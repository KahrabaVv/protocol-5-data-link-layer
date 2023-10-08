#include<iostream>
#include"Go_Back_N.h"
#include"protocol.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

/* Wait for an event to happen; return its type in event. */

void wait_for_event(event_type * Event) {
	switch (*Event)
	{
	case frame_arrive:
		cout << "------------Frame arrival----------"<<endl;
		break;
	case cksum_err:
		cout << "--------------checksum error-----------" << endl;
		break;
	case timeout:
		cout << "--------------timeout------------------" << endl;
		break;
	case network_layer_ready:
		cout << "--------------network_layer_ready-----------" << endl;
		break;
	default:
		break;
	}	
}

/*fetch a packet from the network layer for transmission on the channel.*/
void from_network_layer(packet* p) {
	cout << "From network layer ----> Datalink layer" << endl;
}

/* Deliver information from an inbound frame to the network layer. */
void to_network_layer(packet* p) {
	cout << "From DataLink layer ----> Network layer" << endl;
}
/* Go get an inbound frame from the physical layer and copy it to a data link. */
void from_physical_layer(frame* r)
{
	cout << "From physical layer ----> datalink layer" << endl;

}
/* Pass the frame to the physical layer for transmission. */
void to_physical_layer(frame* s) {
	cout << "From datalink layer ----> physical layer" << endl;
}
/*Start the clock running and enable the timeout event. */
//let the timer be 5 sec to be visual
void start_timer(seq_nr k) {
	int i = 5;
	while (i--) {
		cout << i << endl;
		Sleep(1000);//milli second
	}

}

void stop_timer(seq_nr k) {
	cout << "Stopping the timer" << endl;
}
/* Start an auxiliary timer and enable the ack timeout event. */
void start_ack_timer() {
	int i = 5;
	while (i--) {
		cout << i << endl;
		Sleep(100);//milli second
	}

}
/* Stop the auxiliary timer and disable the ack timeout event. */
void stop_ack_timer() {
	cout << "Stopping the ack timer" << endl;

}
/* Allow the network layer to cause a network layer ready event. */
void enable_network_layer(){
	cout << "--Enabling Network layer--"<<endl;
}
/* Forbid the network layer from causing a network layer ready event. */
void disable_network_layer() {
	cout << "---Disabling network layer---" << endl;
}



int main() {

	return 0;
}