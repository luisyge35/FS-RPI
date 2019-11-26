#include "cansend.h"
#include <string>
#include <iostream>

/* FUNCIONES DE LIB.H*/
#define CANID_DELIM '#'
#define DATA_SEPERATOR '.'

unsigned char asc2nibble(char c) {

	if ((c >= '0') && (c <= '9'))
		return c - '0';

	if ((c >= 'A') && (c <= 'F'))
		return c - 'A' + 10;

	if ((c >= 'a') && (c <= 'f'))
		return c - 'a' + 10;

	return 16; /* error */
}
int parse_canframe(char *cs, struct canfd_frame *cf) {
	/* documentation see lib.h */

	int i, idx, dlen, len;
	int maxdlen = CAN_MAX_DLEN;
	int ret = CAN_MTU;
	unsigned char tmp;

	len = strlen(cs);
	//printf("'%s' len %d\n", cs, len);

	memset(cf, 0, sizeof(*cf)); /* init CAN FD frame, e.g. LEN = 0 */

	if (len < 4)
		return 0;

	if (cs[3] == CANID_DELIM) { /* 3 digits */

		idx = 4;
		for (i=0; i<3; i++){
			if ((tmp = asc2nibble(cs[i])) > 0x0F)
				return 0;
			cf->can_id |= (tmp << (2-i)*4);
		}

	} else if (cs[8] == CANID_DELIM) { /* 8 digits */

		idx = 9;
		for (i=0; i<8; i++){
			if ((tmp = asc2nibble(cs[i])) > 0x0F)
				return 0;
			cf->can_id |= (tmp << (7-i)*4);
		}
		if (!(cf->can_id & CAN_ERR_FLAG)) /* 8 digits but no errorframe?  */
			cf->can_id |= CAN_EFF_FLAG;   /* then it is an extended frame */

	} else
		return 0;

	if((cs[idx] == 'R') || (cs[idx] == 'r')){ /* RTR frame */
		cf->can_id |= CAN_RTR_FLAG;

		/* check for optional DLC value for CAN 2.0B frames */
		if(cs[++idx] && (tmp = asc2nibble(cs[idx])) <= CAN_MAX_DLC)
			cf->len = tmp;

		return ret;
	}

	if (cs[idx] == CANID_DELIM) { /* CAN FD frame escape char '##' */

		maxdlen = CANFD_MAX_DLEN;
		ret = CANFD_MTU;

		/* CAN FD frame <canid>##<flags><data>* */
		if ((tmp = asc2nibble(cs[idx+1])) > 0x0F)
			return 0;

		cf->flags = tmp;
		idx += 2;
	}

	for (i=0, dlen=0; i < maxdlen; i++){

		if(cs[idx] == DATA_SEPERATOR) /* skip (optional) separator */
			idx++;

		if(idx >= len) /* end of string => end of data */
			break;

		if ((tmp = asc2nibble(cs[idx++])) > 0x0F)
			return 0;
		cf->data[i] = (tmp << 4);
		if ((tmp = asc2nibble(cs[idx++])) > 0x0F)
			return 0;
		cf->data[i] |= tmp;
		dlen++;
	}
	cf->len = dlen;

	return ret;
}





using namespace std;
Ccan::Ccan(char *Can_Address)
{

	//system("sudo mobprobe vcan");
	//system("sudo ip link add dev vcan0 type vcan");
	//system("sudo ip link set up vcan0");


	//string Kernel_message =  "sudo /sbin/ip link set ";
	//Kernel_message = Kernel_message + string(Can_Address)+" up type can bitrate 500000";
	/*---------------------ENABLE TO EXECUTE ON TERMINAL---------------------*/
	//system(Kernel_message);
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

void Ccan::SetFrame(int id, uint16_t data){
	//frame.can_id = id;
	//frame.data[0] = data;
	//frame.data[1] = data;
}

void Ccan::Write(char* data)
{
	required_mtu = parse_canframe(data, &frame);
	/* ensure discrete CAN FD length values 0..8, 12, 16, 20, 24, 32, 64 */
	//frame->len = can_dlc2len(can_len2dlc(frame->len));
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
