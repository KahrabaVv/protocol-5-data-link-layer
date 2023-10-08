#define MAX_SEQ 7
typedef enum { frame_arrive, cksum_err, timeout, network_layer_ready } event_type;
static bool between(seq_nr a, seq_nr b, seq_nr c);
static void send_data(seq_nr frame_nr, seq_nr frame_expected, packet buffer[]);
void Go_Back_N(void);


