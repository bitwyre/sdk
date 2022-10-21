import json
import hmac
from urllib import response
import websocket

from websocket import WebSocket
from time import time_ns
from hashlib import sha256, sha512

from public import PublicBitwyreWSClient

from utils import (
    BASE_URL,
    PRINT_DEBUGS,
    parse_codes
)



def sign(secret_key: str, uri_path: str, payload: str):
    nonce = int(time_ns())
    payload = json.dumps(payload, separators=(',', ':'))

    json_payload = json.dumps(payload)
    json_payload = json.dumps(json_payload)
 
    checksum = sha256(str(json_payload).encode("utf-8")).hexdigest()
    nonce_checksum = sha256(str(nonce).encode("utf-8") + str(checksum).encode("utf-8")).hexdigest()
    signature = hmac.new(
        secret_key.encode("utf-8"), uri_path.encode("utf-8") + nonce_checksum.encode("utf-8"), sha512
    ).hexdigest()

    return (nonce, checksum, signature, payload)

class PrivateBitwyreWSClient:
    def __init__(
        self,
        url:str = BASE_URL,
        api_key:str = None,
        api_secret:str = None,
        debugs:str = PRINT_DEBUGS,
    ):
        websocket.enableTrace(debugs)
        self.url = url
        self.uri = ""
        self.ws = websocket.WebSocket()
        self.api_key = api_key
        self.api_secret = api_secret
        self.command = ""
        self.params = {
            "command": None,
            "nonce": None,
            "checksum": None,
            "api_key": self.api_key,
            "api_sign": None,
            "payload": None
        }

    @staticmethod
    def sign(secret_key: str, uri_path: str, payload: str):
        nonce = int(time_ns())
        payload = json.dumps(payload, separators=(',', ':'))

        json_payload = json.dumps(payload)
        json_payload = json.dumps(json_payload)
    
        checksum = sha256(str(json_payload).encode("utf-8")).hexdigest()
        nonce_checksum = sha256(str(nonce).encode("utf-8") + str(checksum).encode("utf-8")).hexdigest()
        signature = hmac.new(
            secret_key.encode("utf-8"), uri_path.encode("utf-8") + nonce_checksum.encode("utf-8"), sha512
        ).hexdigest()

        return (nonce, checksum, signature, payload)

    def close(self):
        self.ws.close()

    def connect(self) -> WebSocket:
        url = self.url + self.uri
        print(f"opening ws connection to {url}")
        self.ws.connect(url)
        print("ws connection success")
        return self.ws

    def send_message(self, message: dict):
        print(f"sending message {message}")
        message = json.dumps(message)

        self.ws.send(message)
        print("sending message success")

    def receive_conn(self, payload:str = None):
        if payload is None:
            payload = ""

        nonce, checksum, signature, payload = self.sign(self.api_secret, self.uri, payload)

        self.params["command"] = self.command
        self.params["nonce"] = nonce
        self.params["checksum"] = checksum
        self.params["api_sign"] = signature
        self.params["payload"] = payload

        self.send_message(self.params)

        status_code, response, error_code, error_msg = self.ws.recv()
        success, response, error_code, error_msg = parse_codes(status_code, response, error_code, error_msg)
    
        return success, response, error_code, error_msg

    def account_balance(self) -> WebSocket:
        self.uri = "/ws/private/account/balance"

        self.command = "get"
        self.connect()

        return self.ws

    def account_statement(self) -> WebSocket:
        self.uri = "/ws/private/account/statement"
        self.command = "get"

        self.connect()
        return self.ws

    def create_order(self) -> WebSocket:
        self.uri = "/ws/private/orders/control"
        self.command = "create"

        self.connect()
        return self.ws

    def cancel_order(self) -> WebSocket:
        self.uri = "/ws/private/orders/control"
        self.command = "cancel"

        self.connect()
        return self.ws

    def order_status(self) -> WebSocket:
        self.uri = "/ws/private/orders/status"
        self.command = "get"

        self.connect()
        return self.ws

    def order_events(self) -> WebSocket:
        self.uri = "/ws/private/orders/events"
        self.command = "subscribe"

        self.connect()
        return self.ws

    def trade_histories(self) -> WebSocket:
        self.uri = "/ws/private/orders/events"
        self.command = "get"

        self.connect()
        return self.ws