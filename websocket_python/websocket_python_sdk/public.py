import json
import websocket

from websocket import WebSocket

from utils import (
    BASE_URL,
    PRINT_DEBUGS,
    parse_codes
)

subscription_message = {
    "op": "subscribe",
    "args": None
}

class PublicBitwyreWSClient:
    def __init__(
        self,
        url:str = BASE_URL,
        debugs:str = PRINT_DEBUGS
    ):
        websocket.enableTrace(debugs)
        self.url = url
        self.ws = websocket.WebSocket()

    def close(self):
        self.ws.close()

    def connect(self, url) -> WebSocket:
        print(f"opening ws connection to {url}")
        self.ws.connect(url)
        print("ws connection success")
        return self.ws

    def send_message(self, message: dict):
        print(f"sending message {message}")
        message = json.dumps(message)

        self.ws.send(message)
        print("sending message success")

    def receive_conn(self):
        status_code, response, error_code, error_msg = self.ws.recv()
        success, response, error_code, error_msg = parse_codes(status_code, response, error_code, error_msg)
    
        return success, response, error_code, error_msg

    def server_time(self) -> WebSocket:
        uri = "/ws/public/time"
        return self.connect(self.url+uri)

    def instruments(
        self, 
        instrument:str
    ) -> WebSocket:
        uri = f"/ws/stream?subscribe=instruments:{instrument}"

        subscribe = subscription_message
        subscribe["args"] = [f"instruments:{instrument}"]

        self.connect(self.url+uri)
        self.send_message(subscribe)

        return self.ws

    def ticker(
        self,
        instrument:str
    ) -> WebSocket:
        uri = f"/ws/stream?subscribe=ticker:{instrument}"

        subscribe = subscription_message
        subscribe["args"] = [f"ticker:{instrument}"]

        self.connect(self.url+uri)

        self.send_message(subscribe)

        return self.ws

    def trades(
        self,
        instrument:str
    ) -> WebSocket:
        uri = f"/ws/stream?subscribe=trades:{instrument}"

        subscribe = subscription_message
        subscribe["args"] = [f"trades:{instrument}"]

        self.connect(self.url+uri)

        self.send_message(subscribe)

        return self.ws

    def depth_l2(
        self,
        instrument:str
    ) -> WebSocket:
        uri = f"/ws/stream?subscribe=depthL2:{instrument}"

        subscribe = subscription_message
        subscribe["args"] = [f"depthL2:{instrument}"]

        self.connect(self.url+uri)

        self.send_message(subscribe)

        return self.ws

    def depth_l2_snapshot25(
        self,
        instrument:str
    ) -> WebSocket:
        uri = f"/ws/stream?subscribe=depthL2_25:{instrument}"

        subscribe = subscription_message
        subscribe["args"] = [f"depthL2_25:{instrument}"]

        self.connect(self.url+uri)

        self.send_message(subscribe)

        return self.ws