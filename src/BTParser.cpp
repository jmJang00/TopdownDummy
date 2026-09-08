#include "pch.h"
#include <string>
#include <JParse/Grammar.h>
#include "BTParser.h"
#include "PlayerBT.h"
#include "PlayerNode.h"

BTParser::BTParser()
	: BaseCompiler("BTParser", false, true)
{
}

BTParser::~BTParser()
{
	bt_map::iterator iter = btMap.begin();
	for (; iter != btMap.end(); iter++)
	{
		delete iter->second;
	}
	btMap.clear();
}

void BTParser::Init()
{
	_grammar->DefineSymbol("Tree", SymbolType::Nonterminal);
	_grammar->DefineSymbol("Node", SymbolType::Nonterminal);
	_grammar->DefineSymbol("List", SymbolType::Nonterminal);
	_grammar->DefineSymbol("Arg", SymbolType::Nonterminal);
	_grammar->DefineSymbol("Composite", SymbolType::Nonterminal);
	_grammar->DefineSymbol("Decorator", SymbolType::Nonterminal);
	_grammar->DefineSymbol("Leaf", SymbolType::Nonterminal);
	_grammar->DefineSymbol("Value", SymbolType::Nonterminal);
	_grammar->DefineSymbol("sequence", SymbolType::Keyword);
	_grammar->DefineSymbol("selector", SymbolType::Keyword);
	_grammar->DefineSymbol("decorator", SymbolType::Keyword);
	_grammar->DefineSymbol("leaf", SymbolType::Keyword);
	_grammar->DefineSymbol("tree", SymbolType::Keyword);

	_grammar->AddRule("[Start] -> [Tree]", Grammar::Skip);
	_grammar->AddRule("[Tree] -> {tree} <lbrace> [Node] <rbrace>", Grammar::Skip);
	_grammar->AddRule("[Node] -> [Composite]", Grammar::Skip);
	_grammar->AddRule("[Node] -> [Decorator]", Grammar::Skip);
	_grammar->AddRule("[Node] -> [Leaf]", Grammar::Skip);
	_grammar->AddRule("[List] -> [Node] [List]", Grammar::Skip);
	_grammar->AddRule("[List] -> <epsilon>", Grammar::Skip);
	_grammar->AddRule("[Composite] -> {sequence} <lbrace> [List] <rbrace>", Grammar::Skip);
	_grammar->AddRule("[Composite] -> {selector} <lbrace> [List] <rbrace>", Grammar::Skip);
	_grammar->AddRule("[Arg] -> [Value]", Grammar::Skip);
	_grammar->AddRule("[Arg] -> <epsilon>", Grammar::Skip);
	_grammar->AddRule("[Value] -> <number>", Grammar::CreateNumber);
	_grammar->AddRule("[Decorator] -> {decorator} <id> <lparen> [Arg] <rparen> <lbrace> [Node] <rbrace>", Grammar::Skip);
	_grammar->AddRule("[Leaf] -> {leaf} <id> <lparen> [Arg] <rparen>", Grammar::Skip);

	BaseCompiler::Init();
}

bool BTParser::Evaluate(LCRSTree* tree)
{
	SimplifyTree(tree);

	tree->TraversePostOrder([&](LCRSNode* node)
		{
			LCRSNode* parent = node->GetParent();
			const std::string& name = node->GetData()->symbol->name;
			if (name == "Node" || name == "Value" || name == "Arg")
			{
				parent->DeleteChild(node, false);
			}
			return true;
		});

	if (_verbose)
	{
		tree->Print(tree->GetRoot(), 0);
	}

	BaseNode* root = nullptr;
	bool ret = false;
	ret = tree->TraversePostOrder([&](LCRSNode* node)
		{
			const std::string& name = node->GetData()->GetSymbolName();
			if (name == "Tree")
			{
				LCRSNode* kind = node->GetChild(0);
				LCRSNode* child = node->GetChild(1);
				root = (BaseNode*)child->GetData()->ptr;
			}
			else if (name == "Decorator")
			{
				LCRSNode* kind = node->GetChild(0);
				LCRSNode* id = node->GetChild(1);
				const std::string& idStr = std::get<std::string>(id->GetData()->dataToken->value);
				if (idStr == "RepeatUntilFail")
				{
					RepeatUntilFailNode* decorator = nullptr;
					if (node->GetChildCount() > 3)
					{
						printf("Too many arguments on Repeat Node\n");
						return false;
					}

					LCRSNode* child = node->GetChild(node->GetChildCount() - 1);
					decorator = new RepeatUntilFailNode();
					decorator->child = (BaseNode*)child->GetData()->ptr;
					node->GetData()->ptr = decorator;
				}
				else if (idStr == "Repeat")
				{
					RepeatNode* decorator = nullptr;
					if (node->GetChildCount() > 4)
					{
						printf("Too many arguments on %s Node\n", idStr.c_str());
						return false;
					}

					int count = 1;
					LCRSNode* value = nullptr;
					ASTData* data = nullptr;
					for (int i = 2; i < node->GetChildCount() - 1; i++)
					{
						data = node->GetChild(i)->GetData();
						if (data->symbol->id != (int)symbol_id::Number)
						{
							printf("Invalid arguments on %s Node", idStr.c_str());
							if (data->symbol->HasTokenValue())
							{
								printf(" (%d:%d)", data->dataToken->lineNum, data->dataToken->lineNum);
							}
							printf("\n");
							return false;
						}
						count = std::get<int>(data->dataToken->value);
					}

					LCRSNode* child = node->GetChild(node->GetChildCount() - 1);
					decorator = new RepeatNode(count);
					decorator->child = (BaseNode*)child->GetData()->ptr;
					node->GetData()->ptr = decorator;
				}
				else if (idStr == "Cooldown")
				{
					CooldownNode* decorator;
					int time = 500;
					LCRSNode* value = nullptr;
					ASTData* data = nullptr;
					if (node->GetChildCount() > 4)
					{
						printf("Too many arguments on %s Node\n", idStr.c_str());
						return false;
					}

					for (int i = 2; i < node->GetChildCount() - 1; i++)
					{
						value = node->GetChild(i);
						data = value->GetData();
						if (data->symbol->id != (int)symbol_id::Number)
						{
							printf("Invalid arguments on %s Node", idStr.c_str());
							if (data->symbol->HasTokenValue())
							{
								printf(" (%d:%d)", data->dataToken->lineNum, data->dataToken->lineNum);
							}
							printf("\n");
							return false;
						}
						time = std::get<int>(data->dataToken->value);
					}

					LCRSNode* child = node->GetChild(node->GetChildCount() - 1);
					decorator = new CooldownNode(time);
					decorator->child = (BaseNode*)child->GetData()->ptr;
					node->GetData()->ptr = decorator;
				}
				else if (idStr == "Random")
				{
					RandomNode* decorator;
					int percent = 50;
					if (node->GetChildCount() > 4)
					{
						printf("Too many arguments on %s Node\n", idStr.c_str());
						return false;
					}

					LCRSNode* value = nullptr;
					ASTData* data = nullptr;
					for (int i = 2; i < node->GetChildCount() - 1; i++)
					{
						value = node->GetChild(i);
						data = value->GetData();
						if (data->symbol->id != (int)symbol_id::Number)
						{
							printf("Invalid arguments on %s Node", idStr.c_str());
							if (data->symbol->HasTokenValue())
							{
								printf(" (%d:%d)", data->dataToken->lineNum, data->dataToken->lineNum);
							}
							printf("\n");
							return false;
						}
						percent = std::get<int>(data->dataToken->value);
					}

					LCRSNode* child = node->GetChild(node->GetChildCount() - 1);
					decorator = new RandomNode(percent);
					decorator->child = (BaseNode*)child->GetData()->ptr;
					node->GetData()->ptr = decorator;
				}
				else
				{
					printf("decorator not found: %s\n", idStr.c_str());
					return false;
				}
			}
			else if (name == "Composite")
			{
				LCRSNode* kind = node->GetChild(0);
				LCRSNode* list = node->GetChild(1);
				if (kind->GetData()->symbol->name == "sequence")
				{
					SequenceNode* sequence = new SequenceNode();
					for (int i = 0; i < list->GetChildCount(); i++)
					{
						LCRSNode* child = list->GetChild(i);
						sequence->children.push_back((BaseNode*)child->GetData()->ptr);
					}
					node->GetData()->ptr = sequence;
				}
				else
				{
					SelectorNode* selector = new SelectorNode();
					for (int i = 0; i < list->GetChildCount(); i++)
					{
						LCRSNode* child = list->GetChild(i);
						selector->children.push_back((BaseNode*)child->GetData()->ptr);
					}
					node->GetData()->ptr = selector;
				}
			}
			else if (name == "Leaf")
			{
				LCRSNode* kind = node->GetChild(0);
				LCRSNode* id = node->GetChild(1);
				const std::string& idStr = std::get<std::string>(id->GetData()->dataToken->value);
				if (idStr == "Delay")
				{
					DelayNode* leafNode = nullptr;
					if (node->GetChildCount() > 3)
					{
						printf("Too many arguments on %s Node\n", idStr.c_str());
						return false;
					}

					LCRSNode* value = nullptr;
					ASTData* data = nullptr;
					int time = 0;
					for (int i = 2; i < node->GetChildCount(); i++)
					{
						value = node->GetChild(i);
						data = value->GetData();
						if (data->symbol->id != (int)symbol_id::Number)
						{
							printf("Invalid arguments on %s Node", idStr.c_str());
							if (data->symbol->HasTokenValue())
							{
								printf(" (%d:%d)", data->dataToken->lineNum, data->dataToken->lineNum);
							}
							printf("\n");
							return false;
						}
						time = std::get<int>(data->dataToken->value);
					}

					leafNode = new DelayNode(time);
					node->GetData()->ptr = leafNode;
				}
				else
				{
					FEnumValue value = PlayerBT::GetType(idStr);
					BaseNode* baseNode = PlayerBT::Parse(value, node);
					if (baseNode != nullptr)
					{
						node->GetData()->ptr = baseNode;
					}
					else
					{
						printf("leaf not found: %s\n", idStr.c_str());
						return false;
					}
				}
			}

			return true;
		});

	if (ret == false)
	{
		tree->TraversePostOrder([](LCRSNode* node)
			{
				if (node->GetData()->ptr != nullptr)
				{
					delete (BaseNode*)node->GetData()->ptr;
				}
				return true;
			});

		return false;
	}

	std::string name = _file->_filename;
	PlayerBT* playerBT = new PlayerBT(root, nullptr);
	bt_map::iterator iter = btMap.find(name);
	if (iter == btMap.end())
	{
		btMap.insert({ name, playerBT });
	}
	else
	{
		delete iter->second;
		iter->second = playerBT;
	}

	return true;
}
