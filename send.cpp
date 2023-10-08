static void send_data(seq_nr frame_nr, seq_nr frame_expected, packet buffer[]){
	/* Construct and send a data frame. */
	frame s; /* scratch variable */
	s.info = buffer[frame_nr]; /* insert packet into frame */
	s.seq = frame nr; /* insert sequence number into frame */
	s.ack = (frame_expected + MAX_SEQ) % (MAX_SEQ + 1);/* piggyback ack */
	to_physical_layer(&s); /* transmit the frame */
	start_timer(frame_nr); /* start the timer running */
}