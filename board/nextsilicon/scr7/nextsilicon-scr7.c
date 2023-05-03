
#include <common.h>
#include <asm/global_data.h>
#include <asm/io.h>

#define SCR7_TEST_PRINT "Running U-boot!"
#define PLATFORM_SCR7_LOG_RING_END_ADDRESS (0xffff8ffff8200000)
#define PLATFORM_LOG_RING_SIZE (0x1000)

struct platform_log_ring {
    uint32_t lock;
    uint32_t head;
    char log[PLATFORM_LOG_RING_SIZE];
};

static void *ns_memcpy(void *dst, const void *src, uint32_t count)
{
    char *tmp1 = dst;
    const char *tmp2 = src;

#define DO_UINT(type)                                                                              \
    if (count >= sizeof(type) && !((uintptr_t)tmp1 % sizeof(type)) &&                              \
        !((uintptr_t)tmp2 % sizeof(type))) {                                                       \
        *(type *)tmp1 = *(type *)tmp2;                                                             \
        tmp1 += sizeof(type);                                                                      \
        tmp2 += sizeof(type);                                                                      \
        count -= sizeof(type);                                                                     \
        continue;                                                                                  \
    }

    while (count > 0) {
        DO_UINT(__uint128_t)
        DO_UINT(uint64_t)
        DO_UINT(uint32_t)
        DO_UINT(uint16_t)
        DO_UINT(uint8_t)
    }

#undef DO_UINT

    return dst;
}
DECLARE_GLOBAL_DATA_PTR;
int board_early_init_f(void)
{
    printf("Early initializing board!\n");
    volatile struct platform_log_ring *ring = (volatile struct platform_log_ring *)((PLATFORM_SCR7_LOG_RING_END_ADDRESS) - PLATFORM_LOG_RING_SIZE - sizeof(uint32_t) - sizeof(uint32_t));
    const char test_print[] = SCR7_TEST_PRINT;
    ring->head = 0;
    ns_memcpy((void *)(ring->log), test_print, sizeof(test_print));
    ring->head = sizeof(test_print);
	return 0;
}

int board_init(void)
{
    printf("Initializing board!\n");
    gd->flags |= GD_FLG_DISABLE_CONSOLE;
    volatile struct platform_log_ring *ring = (volatile struct platform_log_ring *)((PLATFORM_SCR7_LOG_RING_END_ADDRESS) - PLATFORM_LOG_RING_SIZE - sizeof(uint32_t) - sizeof(uint32_t));
    const char test_print[] = SCR7_TEST_PRINT;
    ring->head = 0;
    ns_memcpy((void *)(ring->log), test_print, sizeof(test_print));
    ring->head = sizeof(test_print);
	return 0;
}

int board_late_init(void)
{
    printf("Board late init!\n");
	return 0;
}
// int dram_init(void)
// {
//     printf("DRAM test not implemented!\n");
// 	volatile struct platform_log_ring *ring = (volatile struct platform_log_ring *)((PLATFORM_SCR7_LOG_RING_END_ADDRESS) - PLATFORM_LOG_RING_SIZE - sizeof(uint32_t) - sizeof(uint32_t));
//     const char test_print[] = SCR7_TEST_PRINT;
//     ring->head = 0;
//     ns_memcpy((void *)(ring->log), test_print, sizeof(test_print));
//     ring->head = sizeof(test_print);

// 	return (0);
// }

int testdram(void)
{
    printf("DRAM test not implemented!\n");
	volatile struct platform_log_ring *ring = (volatile struct platform_log_ring *)((PLATFORM_SCR7_LOG_RING_END_ADDRESS) - PLATFORM_LOG_RING_SIZE - sizeof(uint32_t) - sizeof(uint32_t));
    const char test_print[] = SCR7_TEST_PRINT;
    ring->head = 0;
    ns_memcpy((void *)(ring->log), test_print, sizeof(test_print));
    ring->head = sizeof(test_print);

	return (0);
}
