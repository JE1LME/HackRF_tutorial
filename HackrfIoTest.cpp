#include<iostream>
#include<Windows.h>
#include "libhackrf\hackrf.h"

#define FREQ_ONE_MHZ (1000000ull)
#define DEFAULT_BASEBAND_FILTER_BANDWIDTH (15000000)

volatile uint32_t byte_count;
FILE* fd = NULL;
int count = 0;




int rx_callback(hackrf_transfer* transfer) 
{
	size_t bytes_to_write;
	size_t bytes_written;
	int8_t* buf;
	unsigned int i;
	std::cout << transfer->buffer_length <<"  "<<transfer->valid_length<< std::endl;
	std::cout << *(transfer->buffer) << std::endl;
	buf = (int8_t*)transfer->buffer;
	buf += 16384 - 10;
	for (i = 0; i < 10; i++) {
		std::cout<<static_cast<int16_t>(buf[i * 2])<<" ";
		std::cout<<static_cast<int16_t>(buf[i * 2 + 1])<<std::endl;
	}

	if (fd != NULL)
	{
		
			bytes_written = fwrite(transfer->buffer, 1, bytes_to_write, fd);
	}
	count++;
	std::cout << count << std::endl;
	return 0;
}





void main()
{
	static hackrf_device* device = NULL;
	unsigned int lna_gain = 40, vga_gain = 40;
	int result = 0;

	hackrf_init();
	hackrf_open(&device);
	hackrf_set_freq(device, 200*FREQ_ONE_MHZ);
	hackrf_set_sample_rate(device, 10* FREQ_ONE_MHZ);
	result = hackrf_set_baseband_filter_bandwidth(device, DEFAULT_BASEBAND_FILTER_BANDWIDTH);
	result = hackrf_set_vga_gain(device, vga_gain);
	result |= hackrf_set_lna_gain(device, lna_gain);
	hackrf_start_rx(device, rx_callback, NULL);

	Sleep(1000);
	
	hackrf_stop_rx(device);
	hackrf_close(device);
	hackrf_exit();
	std::cout << count << std::endl;
}