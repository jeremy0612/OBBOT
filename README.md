# OBBOT
This is an observation robot made for education reason and farther purposes. !
=================================================================================

#CÁC CHỨC NĂNG CHÍNH CỦA HỆ THỐNG :
	
*Phía MCU:

- MCU xử lý AVR --> Atmega8 (đã có ) 
- Giao tiếp bluetooth với Desktop 
	--> module bluetooth (đã có ) 
		https://nshopvn.com/product/module-thu-phat-bluetooth-hc-06-chip-don-bt06/
- Di chuyển đa hướng 
	--> 4 DC motor, 4 bánh xe đa hướng, khugng xe  
		https://shopee.vn/B%E1%BB%99-khung-xe-4-b%C3%A1nh-Mecanum-di-chuy%E1%BB%83n-%C4%91a-h%C6%B0%E1%BB%9Bng-theo-nhi%E1%BB%81u-ph%C6%B0%C6%A1ng-%E1%BB%A9ng-d%E1%BB%A5ng-trong-robot-khoa-h%E1%BB%8Dc-ch%E1%BA%BF-t%E1%BA%A1o-i.60387211.6658145191?sp_atk=e17c12aa-37f9-4a47-b36d-e5d7c3144d93&xptdk=e17c12aa-37f9-4a47-b36d-e5d7c3144d93
- Đo nồng độ khí dễ cháy 
	--> cảm biến khí gas 
		https://nshopvn.com/product/cam-bien-khi-gas-mq-2/
	--> dữ liệu từ sensor - mcu thông qua ADC
		https://dammedientu.vn/doc-cam-bien-nhiet-lm35-voi-8051
		https://blog.mecsu.vn/ic-adc0808/
- Đo khoảng cách với vật cản
	--> cảm biến khoảng cách  
		https://hshop.vn/products/cam-bien-sieu-am-us-16
	--> dữ liệu từ sensor - mcu sử dụng timer của mcu để đo tính toán		
- Hiển thị MAC address, sensor value 
	--> LCD (đã có) 
- Thông báo gặp vật cản  
	-->Led, buzzer ( đã có ) 
	
*Phía Desktop:

- Nhận dữ liệu từ sensors từ MCU
	--> Python/Pybluez
		https://pypi.org/project/PyBluez/
		https://pybluez.readthedocs.io/en/latest/
- Điều khiển MCU từ xa
	--> C# / WPF
		http://arduino.vn/bai-viet/912-dung-may-tinh-dieu-khien-arduino-thong-qua-bluetooth-voi-c-mot-cai-nhin-toan-dien-ve
	-->Python
		https://pypi.org/project/PyBluez/
		https://pybluez.readthedocs.io/en/latest/
		
Tài liệu tìm hiểu ATMEGA8:
- http://www.hocavr.com/2018/06/bai-2-cau-truc-avr.html
- https://github.com/bartvoet/groupt_microcontrollers/blob/d9c9957b33f6e6d8b3f67e321ee49d96d47d58d8/nl/architecture/architecture_avratmega165.md#stack-en-stackpointer
