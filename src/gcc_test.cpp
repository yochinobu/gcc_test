/***************************************************************/
/*                                                             */
/*      PROJECT NAME :  gcc_test                               */
/*      FILE         :  gcc_test.cpp                           */
/*      DESCRIPTION  :  Main Program                           */
/*                                                             */
/*      This file was generated by e2 studio.                  */
/*                                                             */
/***************************************************************/

#include <iodefine.h>
#include <vector>
#include <array>
#include <TUT_BasicSource/header/setup.h>
#include <Led/Led.h>
#include <UART/UART0.h>
#include <Cmt/Cmt0.h>
#include <functional>
#include <interrupt_handlers.h>

extern std::function< void() > int_excep_sci0_rxi0;

#define NUM 10

UART *uart_print;
Led2 led2;

void interrupt_function_1(){
	uart_print->Printf("again, world 1\n");
}

void interrupt_function_2(){
	uart_print->Printf("again, world 2\n");
}

void interrupt_function_3(){
	static int count = 0;
	uart_print->Printf("again, world 3. No:%d\n",count++);
}

void interrupt_function_4(Led *led){
	static bool led_state = false;
	led_state = !led_state;
	led->output(led_state);
	led2.output(!led_state);
	uart_print->Printf("change, world!\n");
}

int main(void) {
	setup();
	std::vector<int> a;
	int b[NUM];
	std::array<int, NUM> c;
	Led *led = new Led1();
	uart_print = new UART0(UART::B115200, UART::SCI_BUFFERSIZE);
	uart_print->attach_rx_interrupt(interrupt_function_1);
	int function_number = uart_print->attach_rx_interrupt(interrupt_function_2);
	uart_print->attach_rx_interrupt(interrupt_function_3);
	uart_print->detach_rx_interrupt(function_number);
	uart_print->enable_rx_interrupt();

	Cmt *cmt = new Cmt0(1e-4);
	cmt->attach_interrupt(std::bind(interrupt_function_4, led), 0.5);
	cmt->run();

	for(auto i = 0; i < NUM; i++){
		a.push_back(i);
		b[i] = a[i];
		c[i] = a[i];
	}

	led->output(true);
	uart_print->Printf("hello, world!\n");
	uart_print->Printf("thank you, world!\n");

	for(auto i = 0; i < 0; i++);

	while(1) {

	// TODO: add application code here
    }
return 0;
}
