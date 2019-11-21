#include "candsend.h"

Ccan::Ccan(const char *Can_Address)
{
	system("sudo /sbin/ip link set can0 up type can bitrate 500000");
	//addr = Can_Address;
	/* open socket */
	if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
	{
		throw("Error opening socket");
	}
	strncpy(ifr.ifr_name,Can_Address, IFNAMSIZ - 1);
	ifr.ifr_name[IFNAMSIZ - 1] = '\0';
	ifr.ifr_ifindex = if_nametoindex(ifr.ifr_name);
	if (!ifr.ifr_ifindex)
	{
		throw("Error in if_nametoindex");
	}

	memset(&addr, 0, sizeof(addr));
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;
}

Ccan::~Ccan()
{
	close(s);
}

void Ccan::SetFrame(int ID, int *data){
	frame.can_id = ID;
	frame.data[0] = data[0];
	frame.data[1] = data[1];
}

void Ccan::Write(int id, int* data)
{
	SetFrame(id,data);
	/* ensure discrete CAN FD length values 0..8, 12, 16, 20, 24, 32, 64 */
	frame.len = can_dlc2len(can_len2dlc(frame.len));
	/* disable default receive filter on this RAW socket */
	/* This is obsolete as we do not read from the socket at all, but for */
	/* this reason we can remove the receive list in the Kernel to save a */
	/* little (really a very little!) CPU usage.                          */
	setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, NULL, 0);

	if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		throw("Error in binding");
	}
	/* send frame */
	if (write(s, &frame, required_mtu) != required_mtu)
	{
		throw("Error in the writing");
	}
}
