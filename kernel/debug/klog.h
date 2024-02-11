#ifndef KLOG_H
#define KLOG_H

#define klog(fmt, ...) _klog("%s: " fmt "\n", __func__, ##__VA_ARGS__);

void klog_init(void);

void _klog(char *fmt, ...);

#endif /* KLOG_H */
