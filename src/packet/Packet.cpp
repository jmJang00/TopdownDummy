#include "pch.h"
#include "Packet.h"
#include <JNet/CPacket.h>
#include <JNet/CPacketView.h>
#include <JCore/CBucketPool.h>

const wchar_t* gRequestIdStr[] = 
{
    L"100",
    L"102",
    L"400",
    L"401",
    L"603",
    L"604",
    L"605",
    L"607",
    L"608",
    L"609",
    L"611",
    L"612",
    L"700",
    L"720",
    L"724",
    L"726",
    L"902",
    L"1002",
    L"1003",
    L"1011",
    L"1007",
    L"1009",
    L"1100",
    L"1104",
};

const int gRequestIdStrCnt = sizeof(gRequestIdStr) / sizeof(gRequestIdStr[0]);

CPacket& operator<<(CPacket& packet, const Vector2& obj)
{
	packet.PutData((char*)&obj, sizeof(Vector2));
	return packet;
}

CPacket& operator<<(CPacket& packet, const FBufferView<Vector2>& obj)
{
	packet << obj.size;
	packet.PutData((char*)obj.data, sizeof(Vector2) * obj.size);
	return packet;
}

CPacketView& operator>>(CPacketView& packet, Vector2& obj)
{
	packet.GetData((char*)&obj, sizeof(Vector2));
	return packet;
}

CPacketView& operator>>(CPacketView& packet, FBufferView<Vector2>& obj)
{
	packet >> obj.size;
	if (packet.GetLastError() != CPacketView::Default)
	{
		return packet;
	}

	int bytes = sizeof(Vector2) * obj.size;
	if (bytes <= packet.GetBufferSize())
	{
		obj.data = (Vector2*)packet.GetBufferPtr();
		packet.MoveReadPos(bytes);
	}
	else
	{
		packet.SetLastError(CPacketView::ErrorDeserialize);
	}

	return packet;
}
CPacket& operator<<(CPacket& packet, const ItemElem& obj)
{
	packet.PutData((char*)&obj, sizeof(ItemElem));
	return packet;
}

CPacket& operator<<(CPacket& packet, const FBufferView<ItemElem>& obj)
{
	packet << obj.size;
	packet.PutData((char*)obj.data, sizeof(ItemElem) * obj.size);
	return packet;
}

CPacketView& operator>>(CPacketView& packet, ItemElem& obj)
{
	packet.GetData((char*)&obj, sizeof(ItemElem));
	return packet;
}

CPacketView& operator>>(CPacketView& packet, FBufferView<ItemElem>& obj)
{
	packet >> obj.size;
	if (packet.GetLastError() != CPacketView::Default)
	{
		return packet;
	}

	int bytes = sizeof(ItemElem) * obj.size;
	if (bytes <= packet.GetBufferSize())
	{
		obj.data = (ItemElem*)packet.GetBufferPtr();
		packet.MoveReadPos(bytes);
	}
	else
	{
		packet.SetLastError(CPacketView::ErrorDeserialize);
	}

	return packet;
}
CPacket& operator<<(CPacket& packet, const AccountInfo& obj)
{
	packet << obj.id;
	packet << obj.nickname;
	packet << obj.level;
	return packet;
}

CPacket& operator<<(CPacket& packet, const FBufferView<AccountInfo>& obj)
{
	packet << obj.size;
	for (int i = 0; i < obj.size; i++)
	{
		packet << obj.data[i];
	}
	return packet;
}

CPacketView& operator>>(CPacketView& packet, AccountInfo& obj)
{
	packet >> obj.id;
	packet >> obj.nickname;
	packet >> obj.level;
	return packet;
}

CPacketView& operator>>(CPacketView& packet, FBufferView<AccountInfo>& obj)
{
	packet >> obj.size;
	obj.data = (AccountInfo*)packet.GetTempBuffer(sizeof(AccountInfo) * obj.size);
	if (obj.data == nullptr)
	{
		packet.SetLastError(CPacketView::ErrorDeserialize);
		return packet;
	}
	for (int i = 0; i < obj.size; i++)
	{
		packet >> obj.data[i];
	}
	return packet;
}
CPacket& operator<<(CPacket& packet, const ResultInfo& obj)
{
	packet.PutData((char*)&obj, sizeof(ResultInfo));
	return packet;
}

CPacket& operator<<(CPacket& packet, const FBufferView<ResultInfo>& obj)
{
	packet << obj.size;
	packet.PutData((char*)obj.data, sizeof(ResultInfo) * obj.size);
	return packet;
}

CPacketView& operator>>(CPacketView& packet, ResultInfo& obj)
{
	packet.GetData((char*)&obj, sizeof(ResultInfo));
	return packet;
}

CPacketView& operator>>(CPacketView& packet, FBufferView<ResultInfo>& obj)
{
	packet >> obj.size;
	if (packet.GetLastError() != CPacketView::Default)
	{
		return packet;
	}

	int bytes = sizeof(ResultInfo) * obj.size;
	if (bytes <= packet.GetBufferSize())
	{
		obj.data = (ResultInfo*)packet.GetBufferPtr();
		packet.MoveReadPos(bytes);
	}
	else
	{
		packet.SetLastError(CPacketView::ErrorDeserialize);
	}

	return packet;
}
