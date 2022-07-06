/*
Copyright (C) 2021 B&R Danmark
All rights reserved
*/

#ifndef LXI_H
#define LXI_H
#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdint.h>

    /**
 * \file
 * \brief Main lxi header.
 */

    /**
 * \name Common type definitions
 * @{
 */
    typedef struct lxi_options lxi_options_t;
    typedef struct lxi_conn lxi_conn_t;
    typedef struct lxi_img lxi_img_t;
    typedef struct lxi_channel lxi_channel_t;
    typedef struct lxi_area lxi_area_t;
    typedef struct lxi_msg lxi_msg_t;
    typedef struct lxi_timespec lxi_timespec_t;
    /** @} */

    /**
 * \brief Defines constants that specifies the result of an operation.
 */
    typedef enum
    {
        LXI_ERR_OK, ///< Operation successful.
        LXI_ERR_UNKNOWN_SCHEMA,
        LXI_ERR_PARSE_SCHEMA,
        LXI_ERR_NOT_SUPPORTED,
        LXI_ERR_INVALID_OP,
        LXI_ERR_ETH_PROCESS,
        LXI_ERR_ETH_SOCKET,
        LXI_ERR_SEND_BUSY,
        LXI_ERR_NO_MEM,
        LXI_ERR_SYS,
        LXI_ERR_ARG,
        LXI_ERR_NO_CONTENT,
        LXI_ERR_DISCONNECT,
        LXI_ERR_MISSING,
        LXI_ERR_RTH,
        LXI_ERR_FULL,
        LXI_ERR_EMPTY
    } lxi_err_t;

/**
 * \brief Defines an "error" trace level.
 */
#define LXI_TRACE_LEVEL_ERR 1

/**
 * \brief Defines a "warning" trace level.
 */
#define LXI_TRACE_LEVEL_WRN 2

/**
 * \brief Defines an "informational" trace level.
 */
#define LXI_TRACE_LEVEL_INF 3

/**
 * \brief Defines a "debug" trace level.
 *
 * \note Only use this trace level for development and diagnostics.
 */
#define LXI_TRACE_LEVEL_DBG 4

/**
 * \brief Defines a "trace" trace level.
 *
 * \note Output that can flood the output, but which can be used to see that something is happening, like receiving heartbeats
 */
#define LXI_TRACE_LEVEL_MEM 5

/**
 * \brief Defines a "trace" trace level.
 *
 * \note Output that can flood the output, but which can be used to see that something is happening, like receiving heartbeats
 */
#define LXI_TRACE_LEVEL_TRC 6

    /**
 * \brief Defines constants that specifies events that can occur in the lxi
 * stack.
 */
    typedef enum
    {
        /**
     * \brief Event that represents a trace message.
     *
     * The \c trace data argument will be a zero terminated string with a
     * diagnostic message.
     */
        LXI_EV_MESSAGE,
    } lxi_event_t;

    /**
 * \brief Describes a function called when a connection is available.
 *
 * \param conn Related connection object.
 */
    typedef void (*lxi_connect_fn)(lxi_conn_t *conn);

    /**
 * \brief Describes a function called when a connection is closed.
 *
 * \param conn Closed connection.
 */
    typedef void (*lxi_disconnect_fn)(lxi_conn_t *conn);

    /**
 * \brief Describes a function called when asynchronous data is received using a
 * channel.
 *
 * This callback might be invoked multiple times for the same message. Use the
 * is_last flag of lxi_msg_t to decide if more data is expected.
 *
 * \param channel Related channel object.
 * \param msg Received data.
 */
    typedef void (*lxi_async_recv_fn)(lxi_channel_t *channel, lxi_msg_t *msg);

    /**
 * \brief Describes a function called when asynchronous data has been sent using
 * a channel.
 *
 * When this callback is invoked, the associated channel is ready for another
 * send operation.
 *
 * \param channel Related channel object.
 * \param res Result of the channel send.
 */
    typedef void (*lxi_async_send_fn)(lxi_channel_t *channel, lxi_err_t res);

    /**
 * \brief Describes a function called when synchronous input data is available
 * for an area.
 *
 * When invoked, lxi_area_read() should be used to transfer the data to the
 * area input image. Not reading the data from the area, might prevent the
 * remote system from writing more data to the same area.
 *
 * \param area Area that has been changed.
 * \param img Synchronous image with available data.
 */
    typedef void (*lxi_sync_read_fn)(lxi_area_t *area, lxi_img_t *img);

    /**
 * \brief Describes a function called when synchronous output data has been
 * read/sent and the area can be written to.
 *
 * Use this callback to detect when an area is ready for another write
 * operation.
 *
 * \param area Area that has been changed.
 */
    typedef void (*lxi_sync_write_fn)(lxi_area_t *area);

    /**
 * \brief Describes a function called when a traceable event occur in the lxi
 * stack.
 *
 * \param conn Related connection object.
 * \param event Traceable event.
 * \param level The level at which the event occurred.
 * \param data Event specific data.
 */
    typedef void (*lxi_trace_fn)(lxi_conn_t *conn, lxi_event_t event, int level,
                                 void *data);

    /**
 * \brief Describes a function called memory need to be allocated.
 *
 * \param size Size if the requested memory.
 * \return Pointer to the start of the allocated memory or \c NULL if the
 *         allocation failed.
 */
    typedef void *(*lxi_malloc_fn)(size_t size);

    /**
 * \brief Describes a function called to free previously allocated memory.
 *
 * Will only be invoked with pointers to memory previously allocated using
 * lxi_malloc_fn.
 *
 * \param ptr Pointer to the start of the memory that should be freed.
 */
    typedef void (*lxi_free_fn)(void *ptr);

    /**
 * \brief Represents a point in time with nanosecond precision.
 */
    struct lxi_timespec
    {
        uint32_t sec;  /**< Seconds */
        uint32_t nsec; /**< Nanoseconds */
    };

    /**
 * \brief Contains options for a connection.
 */
    struct lxi_options
    {
        /**
     * \brief Callback invoked when a traceable event is detected.
     *
     * Cannot be changed after the connection is initialized.
     */
        lxi_trace_fn trace_callback;

        /**
     * \brief Level used for trace events.
     *
     * If zero, no events are traced. Otherwise it can be set to one of the
     * following levels:
     *   - LXI_TRACE_LEVEL_ERR
     *   - LXI_TRACE_LEVEL_WRN
     *   - LXI_TRACE_LEVEL_INF
     *   - LXI_TRACE_LEVEL_DBG
     *
     * Can be changed after the connection is initialized.
     */
        int trace_level;

        /**
     * \brief Custom function used to perform memory allocation or \c NULL if
     * not specified.
     *
     * Cannot be changed after the connection is initialized.
     */
        lxi_malloc_fn malloc_callback;

        /**
     * \brief Custom function used to free allocated memory or \c NULL if not
     * specified.
     *
     * Cannot be changed after the connection is initialized.
     */
        lxi_free_fn free_callback;

        /**
     * \brief Interval in milliseconds used to send heartbeats from the node to
     * the master.
     *
     * \note The heartbeat might not be valid for all connection types.
     *
     * Cannot be changed after the connection is initialized.
     */
        uint32_t heartbeat_interval;

        /**
     * \brief Timeout in milliseconds used to detect an unresponsive connection.
     *
     * \note The heartbeat might not be valid for all connection types.
     *
     * Cannot be changed after the connection is initialized.
     */
        uint32_t heartbeat_timeout;

        /**
     * \brief Timeout in milliseconds if the process thread need to yield (block
     * for I/O) during a process cycle.
     *
     * Can be changed after the connection is initialized.
     */
        int yield_timeout;

        /**
     * \brief Size in bytes of blocks used to receive and send data.
     *
     * Cannot be changed after the connection is initialized.
     */
        size_t io_block_size;
    };

    /**
 * \brief Represents a connection to a remote host.
 */
    struct lxi_conn
    {
        /**
     * \brief Application defined pointer. Will not be used or touched by lxi.
     */
        void *data;

        /** \cond PRIVATE */

        lxi_options_t *opt;

        lxi_trace_fn trace;
        lxi_malloc_fn malloc;
        lxi_free_fn free;

        uint32_t hb_interval;
        uint32_t hb_timeout;

        lxi_connect_fn connect;
        lxi_disconnect_fn disconnect;

        void *transport;
        lxi_timespec_t clock_now;

        lxi_channel_t *channel_head;
        size_t channel_cnt;

        lxi_area_t *area_head;
        size_t area_cnt;

        /** \endcond */
    };

/**
 * \brief Size of the contract, containing all areas and channels (including their names). approx. (CHANNEL_NAME_MAX+10)*(channels+areas)
 */
#define CONTRACT_BUFFER_SIZE 304800

/**
 * \brief Maximum number of characters used in a channel name.
 */
#define LXI_CHANNEL_NAME_MAX 256

    /**
 * \brief Represents a channel used to send and receive asynchronous data.
 */
    struct lxi_channel
    {
        /**
     * \brief Name of the channel.
     */
        char name[LXI_CHANNEL_NAME_MAX + 1];

        /**
     * \brief Channel type identifier.
     */
        uint32_t type;

        /**
     * \brief Channel version number.
     */
        uint32_t ver;

        /**
     * \brief Channel version number used by the remote system.
     */
        uint32_t ver_other;

        /**
     * \brief Application defined pointer. Will not be used or touched by lxi.
     */
        void *data;

        /** \cond PRIVATE */

        lxi_conn_t *conn;
        lxi_channel_t *next;

        // Channel id used to identify a channel at the remote sys.
        int id;
        int remote_id;

        // State used to track a pending send.
        const uint8_t *send_data;
        size_t send_len;

        // Callbacks.
        lxi_async_recv_fn recv_callback;
        lxi_async_send_fn send_callback;

        /** \endcond */
    };

    /**
 * \brief Represents a synchronous image exchanged with a remote host.
 */
    struct lxi_img
    {
        /**
     * \brief Size (in bytes) of the image.
     */
        size_t size;

        /**
     * \brief Pointer to the image data.
     */
        uint8_t *data;
    };

    /**
 * \brief Represents an area used to read and write synchronous data.
 */
    struct lxi_area
    {
        /**
     * \brief Name of the area.
     */
        char name[LXI_CHANNEL_NAME_MAX + 1];

        /**
     * \brief Area type identifier.
     */
        uint32_t type;

        /**
     * \brief Area version number.
     */
        uint32_t ver;

        /**
     * \brief Area version number used by the remote system.
     */
        uint32_t ver_other;

        /**
     * \brief Application defined pointer. Will not be used or touched by lxi.
     */
        void *data;

        /** \cond PRIVATE */

        lxi_conn_t *conn;
        lxi_area_t *next;
        void *ctx;

        // Area id used to identify an area at the remote system.
        int id;
        int remote_id;

        lxi_img_t *in;
        lxi_img_t *out;

        lxi_sync_read_fn read_callback;
        lxi_sync_write_fn write_callback;

        /** \endcond */
    };

    /**
 * \brief Represents a message or part of message received using a channel.
 */
    struct lxi_msg
    {
        /**
     * \brief Pointer to the received data.
     */
        const uint8_t *data;

        /**
     * \brief Size (in bytes) of the received data.
     */
        size_t length;

        /**
     * \brief Non-zero if this is the last part of the current message being
     * received.
     */
        uint8_t is_last;
    };

    /**
 * \brief Initialize the lxi_options_t structure.
 *
 * Always initialize lxi_options_t before assigning custom values.
 *
 * \param opt Pointer to the options that will be initialized.
 */
    lxi_err_t lxi_opt_init(lxi_options_t *opt);

    /**
 * \brief Initialize the lxi_channel_t structure.
 *
 * The lxi_channel_t data field is reserved for the application and will not be
 * touched.
 *
 * \note A channel must be initialized before the associated connection is
 * opened.
 *
 * \param channel Pointer to the channel the will be initialized.
 * \param conn Pointer to the connection that the channel will be associated
 *             with.
 * \param name Name of the channel. Max 16 characters.
 * \param type Type of the channel. Must match the remote channel type.
 * \param ver Version of the channel.
 * \param recv_callback Callback that will be called when new channel data is
 *                      received.
 * \param send_callback Callback that will be called when the data has been
 *                      sent.
 */
    lxi_err_t lxi_channel_init(lxi_channel_t *channel, lxi_conn_t *conn,
                               const char *name, uint32_t type, uint32_t ver,
                               lxi_async_recv_fn recv_callback,
                               lxi_async_send_fn send_callback);

    /**
 * \brief Sends asynchronous data using the specified channel.
 *
 * Should not be called until the associated channel connection is opened.
 * Since the call is asynchronous, it will not block while waiting for the data
 * to be sent.
 *
 * \param channel Channel used to identify the data that will be sent.
 * \param data Pointer to the data area that will be sent.
 * \param size Size (in bytes) of the data area.
 */
    lxi_err_t lxi_channel_send(lxi_channel_t *channel, const uint8_t *data,
                               size_t size);

    /**
 * \brief Initialize the lxi_img_t structure.
 *
 * \note The image data pointer must remain valid for as long as the lxi stack
 * is using the image.
 *
 * \param img Image to initialize.
 * \param data Pointer to the data area represented by the image.
 * \param size Size (in bytes) of the data area.
 */
    lxi_err_t lxi_img_init(lxi_img_t *img, uint8_t *data, size_t size);

    /**
 * \brief Initialize the lxi_area_t structure.
 *
 * The lxi_area_t data field is reserved for the application and will not be
 * touched.
 *
 * \note An area must be initialized before the associated connection is
 * opened.
 *
 * \param area Area to initialize.
 * \param conn Pointer to the connection that the channel will be associated
 *             with.
 * \param name Unique name used to identify the area.
 * \param type Type of the area. Must match the remote area type.
 * \param ver Version of the area.
 * \param input Image used to store data that is read.
 * \param output Image used to store data that is written.
 * \param read_cb Optional callback invoked when new data is available,
 *                otherwise NULL.
 * \param write_cb Optional callback invoked when written data has been
 *                 read/sent, otherwise NULL.
 */
    lxi_err_t lxi_area_init(lxi_area_t *area, lxi_conn_t *conn, const char *name,
                            uint32_t type, uint32_t ver, lxi_img_t *input,
                            lxi_img_t *output, lxi_sync_read_fn read_cb,
                            lxi_sync_write_fn write_cb);

    /**
 * \brief Writes the area output image to the remote connection.
 *
 * \param area Area to write.
 */
    lxi_err_t lxi_area_write(lxi_area_t *area);

    /**
 * \brief Reads the current state of the remote connection to the input image.
 *
 * Should only be used to perform sporadic reads. For a continuous transfer of
 * data, prefer to used the area read callback.
 *
 * \param area Area to read.
 */
    lxi_err_t lxi_area_read(lxi_area_t *area);

    /**
 * \brief Initialize the lxi_connection_t structure.
 *
 * This will only initialize the connection object. It will need to be opened
 * separately using lxi_conn_open(). The connection object must first be
 * initialized before it can be used by any other function.
 *
 * The lxi_conn_t data field is reserved for the application and will not be
 * touched.
 *
 * \param conn Connection that will be initialized.
 * \param options Options describing the connection.
 */
    lxi_err_t lxi_conn_init(lxi_conn_t *conn, lxi_options_t *options);

    /**
 * \brief Opens the specified connection.
 *
 * Open will create the listening side in the LxI connection. The other side
 * must be using lxi_conn_connect().
 *
 * The type of the connection is decided based on the format of the destination
 * connection string. The connection string is a URI as defined by RFC3986. It
 * supports the following schemes:
 *
 * | Scheme | Description           |
 * |--------|-----------------------|
 * | shm    | Shared memory.        |
 * | eth    | Standard Ethernet     |
 * | plk    | Not implemented       |
 *
 * Each scheme has its own specific syntax.
 *
 * # Powerlink
 *
 * The powerlink syntax is defined as:
 *
 *     plk://<node>,<ip>
 *
 * Where `<node>` is the powerlink node number and `<ip>` the IP address used to
 * transport asynchronous data.
 *
 * # Shared memory
 *
 * When running on the RTS Hypervisor, the syntax is defined as:
 *
 *     shm://<area>,<ip>:<port>
 *
 * Where `<area>` is the name of the shared memory area as defined when the RTS
 * hypervisor is configured, the `<ip>` is the IP address and `<port>` is the
 * port that will be used.
 *
 * # Ethernet
 *
 * When using standard Ethernet, the syntax is defined as:
 *
 *     shm://<ip:port>
 *
 * Where `<ip>` is the IP address and `<port>` is the port that will be used.
 *
 * \note The connection must be initialized before it can be opened.
 *
 * \param conn Connection that should be opened.
 * \param dest Connection string describing how the connection is performed.
 * \param conncb Callback invoked when the connection is opened.
 * \param dconncb Callback invoked when the connection is disconnected.
 */
    lxi_err_t lxi_conn_open(lxi_conn_t *conn, const char *dest,
                            lxi_connect_fn conncb, lxi_disconnect_fn dconncb);

    /**
 * \brief Connects to a remote connection.
 *
 * Connect will connect to an already opened remote system. The other side must
 * be using lxi_conn_open().
 *
 * For a description of the connection string, see lxi_conn_open().
 *
 * \note The connection must be initialized before it can be connected.
 *
 * \param conn Connection that should be connected.
 * \param dest Connection string describing how the connection is performed.
 * \param conncb Callback invoked when the connection is opened.
 * \param dconncb Callback invoked when the connection is disconnected.
 */
    lxi_err_t lxi_conn_connect(lxi_conn_t *conn, const char *dest,
                               lxi_connect_fn conncb, lxi_disconnect_fn dconncb);

    /**
 * \brief Gets the current connection clock.
 *
 * This clock is only used for relative comparisons and should not be used as an
 * absolute reference to a point in time. Will always be monotonic.
 *
 * \param conn Related connection.
 * \param tim Time value that will be assigned the current clock.
 */
    lxi_err_t lxi_conn_now(lxi_conn_t *conn, lxi_timespec_t *tim);

    /**
 * \brief Process the specified connection.
 *
 * Runs the LxI main loop. Must be called to process an opened connection.
 *
 * \param conn Connection to process.
 */
    lxi_err_t lxi_conn_process(lxi_conn_t *conn);

    /**
 * \brief Closes the specified connection.
 *
 * Performs cleanup and graceful shutdown of an opened connection.
 *
 * \param conn Connection to close.
 */
    lxi_err_t lxi_conn_close(lxi_conn_t *conn);

#ifdef __cplusplus
}
#endif
#endif // LXI_H
