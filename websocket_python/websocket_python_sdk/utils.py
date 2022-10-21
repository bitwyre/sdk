
BASE_URL = "wss://api.bitwyre.com"
PRINT_DEBUGS = False

def exit_message(response, error_code, error_msg):
    print("")
    print(" ================ ")
    print(" ================ CONNECT FAILED ================ ")
    print(f"Host response {response}")
    print(f"Host error codes {error_code}")
    print(f"Host error message {error_msg}")
    print(f"Exiting")

def parse_codes(status_code, response, error_code, error_msg):
    """
    Websocket STATUS OPERATION CODE
    0: Continue next packet
    1: returned text message
    2: returned binary message
    3, 4, 5, 6, 7: Unsupported RSV
    8: Connection is closed by host
    9: Ping request
    a: Pong answer

    returns:
        success: bool
        response: string
        connection status: string
        backend message: string
    """
    
    if status_code in [0, 1, 2]:
        # all good
        return (True, response, {"code": status_code, "msg": "all good, connection alive"}, error_msg)
    elif status_code in [3, 4, 5, 6, 7]:
        return (False, response, {"code": status_code, "msg": "rsv is not supported, connection still open"}, error_msg)
    elif status_code == 8:
        return (False, response, {"code": status_code, "msg": "Connection is terminated by host"}, error_msg)
    elif status_code == 9:
        return (True, response, {"code": status_code, "msg": "Counterparty ask for ping"}, error_msg)
    elif status_code in ['a', 'A']:
        return (True, response, {"code": status_code, "msg": "Counterparty pong answer"}, error_msg)