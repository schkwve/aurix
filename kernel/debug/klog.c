#include <debug/klog.h>
#include <dd/uart/uart.h>

#include "printf.h"

void _klog(char *fmt, ...)
{
	va_list ptr;
	char klog_buffer[4096];

	va_start(ptr, fmt);

	vsnprintf((char *)&klog_buffer, -1, fmt, ptr);
	uart_write(klog_buffer);

	va_end(ptr);
}
