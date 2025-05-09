#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/io.h>

#define DRIVER_NAME "gpio_raw_driver"

struct gpio_raw_dev {
    void __iomem *base;
    u32 gpio_num;
};

static int gpio_raw_probe(struct platform_device *pdev)
{
    struct gpio_raw_dev *dev;
    struct resource *res;

    dev = devm_kzalloc(&pdev->dev, sizeof(*dev), GFP_KERNEL);
    if (!dev)
        return -ENOMEM;

    res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    dev->base = devm_ioremap_resource(&pdev->dev, res);
    if (IS_ERR(dev->base))
        return PTR_ERR(dev->base);

    if (of_property_read_u32(pdev->dev.of_node, "gpio-num", &dev->gpio_num)) {
        dev_err(&pdev->dev, "Failed to get gpio-num\n");
        return -EINVAL;
    }

    dev_info(&pdev->dev, "Mapped GPIO base at %p, GPIO num %u\n", dev->base, dev->gpio_num);

    // ---- Set GPIO function to output (GPFSELn) ----
    u32 fsel_off = (dev->gpio_num / 10) * 4;
    u32 shift = (dev->gpio_num % 10) * 3;
    u32 val = readl(dev->base + fsel_off);
    val &= ~(0x7 << shift);       // clear
    val |=  (0x1 << shift);       // set output (001)
    writel(val, dev->base + fsel_off);

    // ---- Set HIGH (GPSETn) ----
    writel(1 << (dev->gpio_num % 32), dev->base + 0x1C);

    return 0;
}

static int gpio_raw_remove(struct platform_device *pdev)
{
    dev_info(&pdev->dev, "GPIO raw driver removed\n");
    return 0;
}

static const struct of_device_id gpio_raw_of_match[] = {
    { .compatible = "my,gpio-raw", },
    { }
};
MODULE_DEVICE_TABLE(of, gpio_raw_of_match);

static struct platform_driver gpio_raw_driver = {
    .probe  = gpio_raw_probe,
    .remove = gpio_raw_remove,
    .driver = {
        .name           = DRIVER_NAME,
        .of_match_table = gpio_raw_of_match,
    },
};

module_platform_driver(gpio_raw_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("YourName");
MODULE_DESCRIPTION("Raw GPIO driver with ioremap and device tree");
