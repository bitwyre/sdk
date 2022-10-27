import json
import logging

from public import PublicBitwyreWSClient
from private import PrivateBitwyreWSClient

from utils import exit_message

logging.basicConfig(
    format='%(asctime)s     %(message)s',
    filemode='w'
)
logger = logging.getLogger()
logger.setLevel(logging.DEBUG)

API_KEY = ""
API_SECRET = ""


def get_server_time():
    """
    get server time 
    """
    client = PublicBitwyreWSClient()
    client.server_time()
    while True:
        print("")
        print("receiving message")
        success, response, error_code, error_msg = client.receive_conn()
        if not success:
            exit_message(response, error_code, error_msg)
            client.close()
            exit()
        
        response = json.loads(response)
        print("new message")
        print(response)

    ws.close()

def get_instruments(instrument:str):
    """
    get list of supported instruments

    params:
    instrument: str, eg crypto_spot_ID
    
    """
    client = PublicBitwyreWSClient()
    client.instruments(instrument)
    while True:
        print("")
        print("receiving message")
        success, response, error_code, error_msg = client.receive_conn()
        if not success:
            exit_message(response, error_code, error_msg)
            client.close()
            exit()

        response = json.loads(response)
        print("new message")
        print(response)

    ws.close()

def get_ticker(instrument:str):
    """
    Streams new ticker information for an asset pair, if no asset pair specified the websocket service will stream all instruments ticker.

    params:
    instrument: str, eg btc_usdt_spot
    
    """
    client = PublicBitwyreWSClient()
    client.ticker(instrument)
    while True:
        print("")
        print("receiving message")
        success, response, error_code, error_msg = client.receive_conn()
        if not success:
            exit_message(response, error_code, error_msg)
            client.close()
            exit()

        response = json.loads(response)
        print("new message")
        print(response)

    ws.close()

def get_trades(instrument:str):
    """
    Streams new trade information for an asset pair, if no asset pair specified the websocket service will stream all instruments new trade.

    params:
    instrument: str, eg btc_usdt_spot
    
    """
    client = PublicBitwyreWSClient()
    client.trades(instrument)
    while True:
        print("")
        print("receiving message")
        success, response, error_code, error_msg = client.receive_conn()
        if not success:
            exit_message(response, error_code, error_msg)
            client.close()
            exit()
      
        response = json.loads(response)
        print("new message")
        print(response)

    ws.close()

def get_depth_l2(instrument:str):
    """
    Streams full L2 orderbook data.

    params:
    instrument: str, eg btc_usdt_spot
    
    """
    client = PublicBitwyreWSClient()
    client.depth_l2(instrument)
    while True:
        print("")
        print("receiving message")
        success, response, error_code, error_msg = client.receive_conn()
        if not success:
            exit_message(response, error_code, error_msg)
            client.close()
            exit()

        response = json.loads(response)
        print("new message")
        print(response)

    ws.close()

def get_depth_l2_snapshot25(instrument:str):
    """
    Streams orderbook depthL2 top 25 levels for bids and asks.

    params:
        instrument: str, eg btc_usdt_spot
    
    """
    client = PublicBitwyreWSClient()
    client.depth_l2_snapshot25(instrument)
    while True:
        print("")
        print("receiving message")
        success, response, error_code, error_msg = client.receive_conn()
        if not success:
            exit_message(response, error_code, error_msg)
            client.close()
            exit()
        response = json.loads(response)
        print("new message")
        print(response)

    ws.close()

def get_account_balance(
    api_key:str = API_KEY,
    api_secret:str = API_SECRET,
):
    """
    Retrieve all user's fiat and crypto balance.
    params:
        api_key: str 
        api_secret: str
    """
    client = PrivateBitwyreWSClient(
        api_key=api_key,
        api_secret=api_secret
    )
    client.account_balance()
    payload = ""  # payload always empty for balances & statements

    while True:
        print("")
        print(f"receiving message")
        success, response, error_code, error_msg = client.receive_conn(payload=payload)
        if not success:
            exit_message(response, error_code, error_msg)
            client.close()
            exit()

        response = json.loads(response)
        print("new message")
        print(response)

def get_account_statement(
    api_key:str = API_KEY,
    api_secret:str = API_SECRET,
):
    """
    Retrieve user's withdraw and deposit history.
    params:
        api_key: str 
        api_secret: str
    """
    client = PrivateBitwyreWSClient(
        api_key=api_key,
        api_secret=api_secret
    )
    client.account_statement()
    payload = ""  # payload always empty for statements & balance

    while True:
        print("")
        print(f"receiving message")
        success, response, error_code, error_msg = client.receive_conn(payload=payload)
        if not success:
            exit_message(response, error_code, error_msg)
            client.close()
            exit()

        response = json.loads(response)
        print("new message")
        print(response)

def create_order(
    api_key:str = API_KEY,
    api_secret:str = API_SECRET,
):
    """
    Create a new trade order.
    further reading on payload (same as REST): https://docs.bitwyre.com/#opening-a-new-order

    persistent params:
        api_key: str 
        api_secret: str

    basic payload params:
        instrument: str 
        ordtype: int
        side: int
        orderqry: float-string
        price: float-string
    """
    client = PrivateBitwyreWSClient(
        api_key=api_key,
        api_secret=api_secret
    )
    client.create_order()

    while True:
        # you can do something to change payload to your needs per loop
        # eg read db, api calls, kafka consume etc
        
        payload = {
            "instrument": "btc_usdt_spot",
            "side": 1,
            "ordtype": 2,
            "orderqty": "0.0025",
            "price": "16500"
        }

        print("")
        print(f"receiving message")
        success, response, error_code, error_msg = client.receive_conn(payload=payload)
        if not success:
            exit_message(response, error_code, error_msg)
            client.close()
            exit()

        response = json.loads(response)
        print("new message")
        print(response)


def cancel_order(
    api_key:str = API_KEY,
    api_secret:str = API_SECRET,
):
    """
    Cancels open orders by its ID, can be bulk.
    further reading on payload (same as REST): https://docs.bitwyre.com/#ws-orders-cancellation

    persistent params:
        api_key: str 
        api_secret: str

    basic payload params:
        order_ids: list of string -> lists of order id to be cancelled
        qtys: list of float-string -> lists of corresponding qtys to be cancelled
    """
    client = PrivateBitwyreWSClient(
        api_key=api_key,
        api_secret=api_secret
    )
    client.cancel_order()

    while True:
        # you can do something to change payload to your needs per loop
        # eg read db, api calls, kafka consume etc
        
        payload = {
            "order_ids": ["698dff27-4280-42da-9349-097a412f3bc3"],
            "qtys": [-1]
        }

        print("")
        print(f"receiving message")
        success, response, error_code, error_msg = client.receive_conn(payload=payload)
        if not success:
            exit_message(response, error_code, error_msg)
            client.close()
            exit()

        response = json.loads(response)
        print("new message")
        print(response)


def order_status(
    api_key:str = API_KEY,
    api_secret:str = API_SECRET,
):
    """
    Retrieves information on a specific order.

    persistent params:
        api_key: str 
        api_secret: str

    basic payload params:
        orderid: str
    """
    client = PrivateBitwyreWSClient(
        api_key=api_key,
        api_secret=api_secret
    )
    client.order_status()

    while True:
        # you can do something to change payload to your needs per loop
        # eg read db, api calls, kafka consume etc
        
        payload = {
            "orderid": "698dff27-4280-42da-9349-097a412f3bc3",
        }

        print("")
        print(f"receiving message")
        success, response, error_code, error_msg = client.receive_conn(payload=payload)
        if not success:
            exit_message(response, error_code, error_msg)
            client.close()
            exit()

        response = json.loads(response)
        print("new message")
        print(response)

def order_events(
    api_key:str = API_KEY,
    api_secret:str = API_SECRET,
):
    """
    Subscribe to eventual broadcasts on order status changes, can only be filtered by instrument/Asset Pair symbol.

    persistent params:
        api_key: str 
        api_secret: str

    basic payload params:
        instrument: str
    """
    client = PrivateBitwyreWSClient(
        api_key=api_key,
        api_secret=api_secret
    )
    client.order_events()

    while True:
        # you can do something to change payload to your needs per loop
        # eg read db, api calls, kafka consume etc
        
        payload = {
            "instrument": "btc_usdt_spot",
        }

        print("")
        print(f"receiving message")
        success, response, error_code, error_msg = client.receive_conn(payload=payload)
        if not success:
            exit_message(response, error_code, error_msg)
            client.close()
            exit()

        response = json.loads(response)
        print("new message")
        print(response)

def trade_histories(
    api_key:str = API_KEY,
    api_secret:str = API_SECRET,
):
    """
    Subscribe to eventual broadcasts on order status changes, can only be filtered by instrument/Asset Pair symbol.

    persistent params:
        api_key: str 
        api_secret: str

    basic payload params:
        instrument: str, not mandatory
        count: int, number of data to poll, not mandatory
        from_time: bigint, nanosecond precision, not mandatory
        to_time: bigint, nanosecond precision, not mandatory
    """
    client = PrivateBitwyreWSClient(
        api_key=api_key,
        api_secret=api_secret
    )
    client.trade_histories()

    while True:
        # you can do something to change payload to your needs per loop
        # eg read db, api calls, kafka consume etc
        
        payload = {
            "instrument": "btc_idr_spot",
            "from_time": 1537913405774945493,
            "to_time": 2537913405774945493,
            "count": 10
        }

        print("")
        print(f"receiving message")
        success, response, error_code, error_msg = client.receive_conn(payload=payload)
        if not success:
            exit_message(response, error_code, error_msg)
            client.close()
            exit()

        response = json.loads(response)
        print("new message")
        print(response)

if __name__ == "__main__":
    create_order()

    