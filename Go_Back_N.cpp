#include "Go_Back_N.h"
#include "protocol.h"
static bool between(seq_nr a, seq_nr b, seq_nr c) {
	// return true if a <= b < c {b is between a and c}
	if (((a <= b) && (b < c)) || ((c < a) && (a <= b)) || ((b < c) && (c < a)))
		return true;
	else
		return false;
};

static void send_data(seq_nr frame_nr, seq_nr frame_expected, packet buffer[]) {
	frame s;
	s.info = buffer[frame_nr];
	s.seq = frame_nr;
	s.ack = (frame_expected + MAX_SEQ) % (MAX_SEQ + 1);
	to_physical_layer(&s);
	start_timer(frame_nr);
};

void Go_Back_N(void) {
	seq_nr next_frame_to_send;
	seq_nr ack_expected;
	seq_nr frame_expected;
	frame r;
	packet buffer[MAX_SEQ + 1];
	seq_nr nbuffer;
	seq_nr i;
	event_type event;

	enable_network_layer();
	ack_expected = 0;
	next_frame_to_send = 0;
	frame_expected = 0;
	nbuffer = 0;

	while (true)
	{
		wait_for_event(&event);
		switch (event)
		{
		case network_layer_ready:
			from_network_layer(&buffer[next_frame_to_send]);
			nbuffer++;
			send_data(next_frame_to_send, frame_expected, buffer);
			inc(next_frame_to_send);
			break;

		case frame_arrive:
			from_physical_layer(&r);

			if (r.seq == frame_expected)
			{
				to_network_layer(&r.info);
				inc(frame_expected);
			}
			while (between(ack_expected, r.ack,next_frame_to_send))
			{
				nbuffer = nbuffer - 1;
				stop_timer(ack_expected);
				inc(ack_expected);
			}
			break;

		case cksum_err: break;

		case timeout:
			next_frame_to_send = ack_expected;
			for (i = 0; i < nbuffer; i++) {
				send_data(next_frame_to_send, frame_expected, buffer);
				inc(next_frame_to_send);
			}
		default:
			break;
		}
		if (nbuffer < MAX_SEQ)
			enable_network_layer();
		else
			disable_network_layer();
	}
}
