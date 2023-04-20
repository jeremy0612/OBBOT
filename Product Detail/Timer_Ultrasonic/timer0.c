#define F_CPU 2000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint16_t dem = 0;

// Khai báo thanh ghi PORTB
//#define LED PB0

int main() {
  
  DDRB = 0x01;
  PORTB = 0x00;
  // Thiết lập Timer0
  TCCR0 |= (1<< CS02); // chọn bộ chia tần 256
  TCNT0 = 0; // giá trị khởi tạo ban đầu
  TIMSK |= (1<<TOIE0 ); // cho phép ngắt Timer0
  sei(); // cho phép ngắt toàn cục
  
  while (1) {
    // đợi cho đến khi đếm đủ 5 giây
    if (dem >= 30.5) 
    {
      PORTB = ~PORTB;
      dem = 0; // đặt lại giá trị đếm
    }
  }
  
  return 0;
}

// hàm ngắt Timer0
ISR(TIMER0_OVF_vect) {
    TCNT0 =0; // thiết lập giá trị khởi tạo ban đầu
    dem++; // tăng biến đếm
}
