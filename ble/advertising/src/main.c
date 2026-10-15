
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gap.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/addr.h>
#include <zephyr/bluetooth/conn.h>

#include <dk_buttons_and_leds.h>

#define USER_BUTTON DK_BTN1_MSK
#define RUN_STATUS_LED DK_LED1
/* STEP 3.1 - Define an LED to show the connection status */
#define CONNECTION_STATUS_LED   DK_LED2
#define RUN_LED_BLINK_INTERVAL 1000

/* Create the advertising parameter for connectable advertising */
static const struct bt_le_adv_param *adv_param = BT_LE_ADV_PARAM(
	(BT_LE_ADV_OPT_CONN |
	 BT_LE_ADV_OPT_USE_IDENTITY), /* Connectable advertising and use identity address */
	BT_GAP_ADV_FAST_INT_MIN_1, /* 0x30 units, 48 units, 30ms */
	BT_GAP_ADV_FAST_INT_MAX_1, /* 0x60 units, 96 units, 60ms */
	NULL); /* Set to NULL for undirected advertising */

LOG_MODULE_REGISTER(main, 3);

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

struct bt_conn *my_conn = NULL;
static struct k_work adv_work;

/* Declare the advertising packet */
static const struct bt_data ad[] = {
	/* Set the advertising flags */
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	/* Set the advertising packet data  */
	BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};

/* Declare the scan response packet */
static const struct bt_data sd[] = {
	/* Include the 16-bytes (128-Bits) UUID of the LBS service in the scan response packet */
	BT_DATA_BYTES(BT_DATA_UUID128_ALL,
		      BT_UUID_128_ENCODE(0x00001523, 0x1212, 0xefde, 0x1523, 0x785feabcd123)),
};

/* Resume advertising after a disconnection */
static void adv_work_handler(struct k_work *work)
{
	int err = bt_le_adv_start(adv_param, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));

	if (err) {
		printk("Advertising failed to start (err %d)\n", err);
		return;
	}

	printk("Advertising successfully started\n");
}

static void advertising_start(void)
{
	k_work_submit(&adv_work);
}

/* Implement the callback functions */
void on_connected(struct bt_conn *conn, uint8_t err)
{
	if (err) {
		LOG_ERR("Connection error %d", err);
		return;
	}
	LOG_INF("Connected");
	my_conn = bt_conn_ref(conn);

	/* Turn the connection status LED on */
	// ...... maybe in ble/characteristics

	dk_set_led(CONNECTION_STATUS_LED, 1);
}

void on_disconnected(struct bt_conn *conn, uint8_t reason)
{
	LOG_INF("Disconnected. Reason %d", reason);
	bt_conn_unref(my_conn);

	/* Turn the connection status LED off */
	// ...... maybe in ble/characteristics

	dk_set_led(CONNECTION_STATUS_LED, 0);
}

static void on_recycled(void)
{

	// It typically means that you have encountered a disconnection, 
	// and that one of your connections has been unreferenced, 
	// meaning you can start advertising again.

	printk("Connection object available from previous conn. Disconnect is complete!\n");
	advertising_start();
}


// # Nordic: Note that in many of the Bluetooth Low Energy samples, 
// you will not see bt_conn_cb_register() being used. Instead, 
// they use the macro BT_CONN_CB_DEFINE(), 
// which will both define and register these callbacks.

// BT_CONN_CB_DEFINE(conn_callbacks) = {
// 	.recycled = recycled_cb,
// };

/* Declare the connection_callback structure */
struct bt_conn_cb connection_callbacks = {
	.connected              = on_connected,
	.disconnected           = on_disconnected,
	.recycled               = on_recycled,
};

int main(void)
{

	int blink_status = 0;
  int err;
	
  LOG_INF("Starting ble program!\n");

	err = dk_leds_init();
	if (err) {
		LOG_ERR("LEDs init failed (err %d)", err);
		return -1;
	}

  /* Change the random static address */
	bt_addr_le_t addr;
	err = bt_addr_le_from_str("FF:EE:DD:CC:BB:AA", "random", &addr);
	if (err) {
		printk("Invalid BT address (err %d)\n", err);
	}

	err = bt_id_create(&addr, NULL);
	if (err < 0) {
		printk("Creating new ID failed (err %d)\n", err);
	}

	/* Register our custom callbacks */
	err = bt_conn_cb_register(&connection_callbacks);
	if (err) {
		LOG_ERR("Connection callback register failed (err %d)", err);
	}

	err = bt_enable(NULL);
	if (err) {
		LOG_ERR("Bluetooth init failed (err %d)\n", err);
		return -1;
	}

	LOG_INF("Bluetooth initialized\n");

	/* Start connectable advertising */
	k_work_init(&adv_work, adv_work_handler);
	advertising_start();

	LOG_INF("Advertising successfully started\n");

	for (;;) {
		dk_set_led(RUN_STATUS_LED, (++blink_status) % 2);
		k_sleep(K_MSEC(RUN_LED_BLINK_INTERVAL));
	}

}