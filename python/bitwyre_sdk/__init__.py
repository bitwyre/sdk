import sys
import json

import requests
from bitwyre_sdk.config import (
    TIMEOUT,
    URI_PRIVATE_API_BITWYRE,
    URI_PUBLIC_API_BITWYRE,
    URL_API_BITWYRE,
)
from bitwyre_sdk.utils import return_not_ok, return_timeout, sign, Logger

_module_logger = Logger()


class PublicAPI:
    def get_server_time(self) -> (int, dict):
        try:
            response = requests.get(URL_API_BITWYRE + URI_PUBLIC_API_BITWYRE.get("SERVERTIME"), timeout=TIMEOUT)
        except requests.exceptions.Timeout as e:
            _module_logger.debug(e)
            (status_code, results) = return_timeout()
            return (status_code, results)

        if response.status_code != 200:
            _module_logger.debug(f"Error {response.reason}, please check again your request")
            (status_code, results) = return_not_ok(response)
            return (status_code, results)
        _module_logger.debug("Successfully retrieved server time")
        results = response.json()
        status_code = 200
        return (status_code, results)

    def get_asset_pairs(self, market, product, country) -> (int, dict):
        params = {
            "market": market,
            "product": product,
            "country": country,
        }
        try:
            response = requests.get(
                URL_API_BITWYRE + URI_PUBLIC_API_BITWYRE.get("INSTRUMENT"), params=params, timeout=TIMEOUT
            )
        except requests.exceptions.Timeout as e:
            _module_logger.debug(e)
            (status_code, results) = return_timeout()
            return (status_code, results)

        if response.status_code != 200:
            _module_logger.debug(f"Error {response.reason}, please check again your request")
            (status_code, results) = return_not_ok(response)
            return (status_code, results)

        _module_logger.debug("Successfully retrieved server time")
        results = response.json()
        status_code = 200
        return (status_code, results)

    def get_ticker(self, instrument: str) -> dict:
        params = {
            "instrument": instrument,
        }
        try:
            response = requests.get(
                URL_API_BITWYRE + URI_PUBLIC_API_BITWYRE.get("TICKER"), params=params, timeout=TIMEOUT
            )
        except requests.exceptions.Timeout as e:
            _module_logger.debug(e)
            (status_code, results) = return_timeout()
            return (status_code, results)

        if response.status_code != 200:
            _module_logger.debug(f"Error {response.reason}, please check again your request")
            (status_code, results) = return_not_ok(response)
            return (status_code, results)

        _module_logger.debug("Successfully retrieved tickers")
        results = response.json()
        status_code = 200
        return (status_code, results)

    def get_trades(self, trade_num: int, instrument: str) -> dict:
        params = {
            "trade_num": trade_num,
            "instrument": instrument,
        }
        try:
            response = requests.get(
                URL_API_BITWYRE + URI_PUBLIC_API_BITWYRE.get("TRADES"), params=params, timeout=TIMEOUT
            )
        except requests.exceptions.Timeout as e:
            _module_logger.debug(e)
            (status_code, results) = return_timeout()
            return (status_code, results)

        if response.status_code != 200:
            _module_logger.debug(f"Error {response.reason}, please check again your request")
            (status_code, results) = return_not_ok(response)
            return (status_code, results)

        _module_logger.debug("Successfully retrieved trades")
        results = response.json()
        status_code = 200
        return (status_code, results)

    def get_depth(self, instrument: str, depth_num: int) -> dict:
        params = {"instrument": instrument, "depth_num": depth_num}
        try:
            response = requests.get(
                URL_API_BITWYRE + URI_PUBLIC_API_BITWYRE.get("DEPTH"), params=params, timeout=TIMEOUT
            )
        except requests.exceptions.Timeout as e:
            _module_logger.debug(e)
            (status_code, results) = return_timeout()
            return (status_code, results)

        if response.status_code != 200:
            _module_logger.debug(f"Error {response.reason}, please check again your request")
            (status_code, results) = return_not_ok(response)
            return (status_code, results)

        _module_logger.debug("Successfully retrieved depth")
        results = response.json()
        status_code = 200
        return (status_code, results)

    def get_announcements(self) -> dict:
        try:
            response = requests.get(URL_API_BITWYRE + URI_PUBLIC_API_BITWYRE.get("ANNOUNCEMENTS"), timeout=TIMEOUT)
        except requests.exceptions.Timeout as e:
            _module_logger.debug(e)
            (status_code, results) = return_timeout()
            return (status_code, results)

        if response.status_code != 200:
            _module_logger.debug(f"Error {response.reason}, please check again your request")
            (status_code, results) = return_not_ok(response)
            return (status_code, results)

        _module_logger.debug("Successfully retrieved announcements")
        results = response.json()
        status_code = 200
        return (status_code, results)

    def get_assets(self) -> dict:
        try:
            response = requests.get(URL_API_BITWYRE + URI_PUBLIC_API_BITWYRE.get("ASSETS"), timeout=TIMEOUT)
        except requests.exceptions.Timeout as e:
            _module_logger.debug(e)
            (status_code, results) = return_timeout()
            return (status_code, results)

        if response.status_code != 200:
            _module_logger.debug(f"Error {response.reason}, please check again your request")
            (status_code, results) = return_not_ok(response)
            return (status_code, results)

        _module_logger.debug("Successfully retrieved assets")
        results = response.json()
        status_code = 200
        return (status_code, results)

    def get_markets(self) -> dict:
        try:
            response = requests.get(URL_API_BITWYRE + URI_PUBLIC_API_BITWYRE.get("MARKETS"), timeout=TIMEOUT)
        except requests.exceptions.Timeout as e:
            _module_logger.debug(e)
            (status_code, results) = return_timeout()
            return (status_code, results)

        if response.status_code != 200:
            _module_logger.debug(f"Error {response.reason}, please check again your request")
            (status_code, results) = return_not_ok(response)
            return (status_code, results)

        _module_logger.debug("Successfully retrieved markets")
        results = response.json()
        status_code = 200
        return (status_code, results)

    def get_products(self) -> dict:
        try:
            response = requests.get(URL_API_BITWYRE + URI_PUBLIC_API_BITWYRE.get("PRODUCTS"), timeout=TIMEOUT)
        except requests.exceptions.Timeout as e:
            _module_logger.debug(e)
            (status_code, results) = return_timeout()
            return (status_code, results)

        if response.status_code != 200:
            _module_logger.debug(f"Error {response.reason}, please check again your request")
            (status_code, results) = return_not_ok(response)
            return (status_code, results)

        _module_logger.debug("Successfully retrieved products")
        results = response.json()
        status_code = 200
        return (status_code, results)


class PrivateAPI:
    def __init__(self, secret_key: str, api_key: str):
        self.secret_key = secret_key
        self.api_key = api_key

    def get_account_balance(self, page: int = 1, per_page: int = 50) -> (int, dict):
        payload = ""

        uri_path = URI_PRIVATE_API_BITWYRE.get("ACCOUNT_BALANCE")
        (nonce, checksum, signature) = sign(self.secret_key, uri_path, payload)
        headers = {"API-Key": self.api_key, "API-Sign": signature}
        params = {"nonce": nonce, "checksum": checksum, "payload": payload, "page": page, "per_page": per_page}
        try:
            response = requests.get(URL_API_BITWYRE + uri_path, headers=headers, params=params, timeout=TIMEOUT)
        except requests.exceptions.Timeout as e:
            _module_logger.debug(e)
            (status_code, results) = return_timeout()
            return (status_code, results)

        if response.status_code != 200:
            _module_logger.debug(f"Error {response.reason}, please check again your request")
            (status_code, results) = return_not_ok(response)
            return (status_code, results)

        _module_logger.debug("Successfully retrieving account balances")
        results = response.json()
        status_code = 200
        return (status_code, results)

    def get_account_statement(self, asset: str = None, page: int = 1, per_page: int = 50) -> (int, dict):
        if asset is None:
            payload = ""
        else:
            payload = json.dumps({"assets": asset})

        uri_path = URI_PRIVATE_API_BITWYRE.get("ACCOUNT_STATEMENT")
        (nonce, checksum, signature) = sign(self.secret_key, uri_path, payload)
        headers = {"API-Key": self.api_key, "API-Sign": signature}
        params = {"nonce": nonce, "checksum": checksum, "payload": payload, "page": page, "per_page": per_page}
        try:
            response = requests.get(URL_API_BITWYRE + uri_path, headers=headers, params=params, timeout=TIMEOUT)
        except requests.exceptions.Timeout as e:
            _module_logger.debug(e)
            (status_code, results) = return_timeout()
            return (status_code, results)

        if response.status_code != 200:
            _module_logger.debug(f"Error {response.reason}, please check again your request")
            (status_code, results) = return_not_ok(response)
            return (status_code, results)

        _module_logger.debug("Successfully retrieving account statements")
        results = response.json()
        status_code = 200
        return (status_code, results)

    def get_transaction_histories(self, page: int = 1, per_page: int = 50) -> (int, dict):
        uri_path = URI_PRIVATE_API_BITWYRE.get("TRANSACTION_HISTORIES")
        payload = ""
        (nonce, checksum, signature) = sign(self.secret_key, uri_path, payload)
        headers = {"API-Key": self.api_key, "API-Sign": signature}
        params = {"nonce": nonce, "checksum": checksum, "payload": payload, "page": page, "per_page": per_page}
        try:
            response = requests.get(URL_API_BITWYRE + uri_path, headers=headers, params=params, timeout=TIMEOUT)
        except requests.exceptions.Timeout as e:
            _module_logger.debug(e)
            (status_code, results) = return_timeout()
            return (status_code, results)

        if response.status_code != 200:
            _module_logger.debug(f"Error {response.reason}, please check again your request")
            (status_code, results) = return_not_ok(response)
            return (status_code, results)

        _module_logger.debug("Successfully retrieving transaction histories")
        results = response.json()
        status_code = 200
        return (status_code, results)

    def get_open_orders(self, instrument: str, from_time: int = None, to_time: int = None, page: int = 1, per_page: int = 50) -> (int, dict):
        uri_path = URI_PRIVATE_API_BITWYRE.get("OPEN_ORDERS")
        payload = {
            "instrument": instrument,
            "from_time": from_time,
            "to_time": to_time,
        }
        payload = json.dumps(payload)
        (nonce, checksum, signature) = sign(self.secret_key, uri_path, payload)
        headers = {"API-Key": self.api_key, "API-Sign": signature}
        params = {"nonce": nonce, "checksum": checksum, "payload": payload, "page": page, "per_page": per_page}
        try:
            response = requests.get(URL_API_BITWYRE + uri_path, headers=headers, params=params, timeout=TIMEOUT)
        except requests.exceptions.Timeout as e:
            _module_logger.debug(e)
            (status_code, results) = return_timeout()
            return (status_code, results)

        if response.status_code != 200:
            _module_logger.debug(f"Error {response.reason}, please check again your request")
            (status_code, results) = return_not_ok(response)
            return (status_code, results)

        _module_logger.debug("Successfully retrieving open orders")
        results = response.json()
        status_code = 200
        return (status_code, results)

    def get_closed_orders(self, instrument: str, from_time: int = None, to_time: int = None, page: int = 1, per_page: int = 50) -> (int, dict):
        uri_path = URI_PRIVATE_API_BITWYRE.get("CLOSED_ORDERS")
        payload = {
            "instrument": instrument,
            "from_time": from_time,
            "to_time": to_time,
        }
        payload = json.dumps(payload)
        (nonce, checksum, signature) = sign(self.secret_key, uri_path, payload)
        headers = {"API-Key": self.api_key, "API-Sign": signature}
        params = {"nonce": nonce, "checksum": checksum, "payload": payload, "page": page, "per_page": per_page}
        try:
            response = requests.get(URL_API_BITWYRE + uri_path, headers=headers, params=params, timeout=TIMEOUT)
        except requests.exceptions.Timeout as e:
            _module_logger.debug(e)
            (status_code, results) = return_timeout()
            return (status_code, results)

        if response.status_code != 200:
            _module_logger.debug(f"Error {response.reason}, please check again your request")
            (status_code, results) = return_not_ok(response)
            return (status_code, results)

        _module_logger.debug("Successfully retrieving closed orders")
        results = response.json()
        status_code = 200
        return (status_code, results)

    def get_order_info(self, order_id: str, page: int = 1, per_page: int = 50) -> (int, dict):
        payload = ""
        uri_path = URI_PRIVATE_API_BITWYRE.get("ORDER_INFO") + "/" + order_id
        (nonce, checksum, signature) = sign(self.secret_key, uri_path, payload)
        headers = {"API-Key": self.api_key, "API-Sign": signature}
        params = {"nonce": nonce, "checksum": checksum, "payload": payload, "page": page, "per_page": per_page}
        try:
            response = requests.get(URL_API_BITWYRE + uri_path, headers=headers, params=params, timeout=TIMEOUT)
        except requests.exceptions.Timeout as e:
            _module_logger.debug(e)
            (status_code, results) = return_timeout()
            return (status_code, results)

        if response.status_code != 200:
            _module_logger.debug(f"Error {response.reason}, please check again your request")
            (status_code, results) = return_not_ok(response)
            return (status_code, results)

        _module_logger.debug("Successfully retrieving order info")
        results = response.json()
        status_code = 200
        return (status_code, results)

    def get_trade_history(
        self, instrument: str, count: int = None, from_time: int = None, to_time: int = None, page: int = 1, per_page: int = 50
    ) -> (int, dict):
        uri_path = URI_PRIVATE_API_BITWYRE.get("TRADE_HISTORY")
        payload = {
            "instrument": instrument,
            "count": count,
            "from_time": from_time,
            "to_time": to_time,
        }
        payload = json.dumps(payload)
        (nonce, checksum, signature) = sign(self.secret_key, uri_path, payload)
        headers = {"API-Key": self.api_key, "API-Sign": signature}
        params = {"nonce": nonce, "checksum": checksum, "payload": payload, "page": page, "per_page": per_page}
        try:
            response = requests.get(URL_API_BITWYRE + uri_path, headers=headers, params=params, timeout=TIMEOUT)
        except requests.exceptions.Timeout as e:
            _module_logger.debug(e)
            (status_code, results) = return_timeout()
            return (status_code, results)

        if response.status_code != 200:
            _module_logger.debug(f"Error {response.reason}, please check again your request")
            (status_code, results) = return_not_ok(response)
            return (status_code, results)

        _module_logger.debug("Successfully retrieving closed orders")
        results = response.json()
        status_code = 200
        return (status_code, results)

    def opening_new_order(
        self,
        instrument: str,
        side: int,
        price: float,
        ordtype: int,
        orderqty: str,
        stoppx: float = None,
        clordid: str = None,
        timeinforce: int = None,
        expiretime: int = None,
        execinst: str = None,
    ) -> (int, dict):
        uri_path = URI_PRIVATE_API_BITWYRE.get("ORDER")
        payload = {"instrument": instrument, "side": side, "price": price, "ordtype": ordtype, "orderqty": orderqty}
        if stoppx is not None:
            payload["stoppx"] = stoppx
        if clordid is not None:
            payload["clordid"] = clordid
        if timeinforce is not None:
            payload["timeinforce"] = timeinforce
        if expiretime is not None:
            payload["expiretime"] = expiretime
        if execinst is not None:
            payload["execinst"] = execinst

        if ordtype == 2 and price is None:
            status_code = 422
            results = {}
            _module_logger.debug("Limit order price cannot be null")
            results["error"] = ["Limit order price cannot be null"]
            results["result"] = {}
            return (status_code, results)

        if ordtype == 1:
            payload["price"] = 0

        payload = json.dumps(payload)
        (nonce, checksum, signature) = sign(self.secret_key, uri_path, payload)
        headers = {
            "API-Key": self.api_key,
            "API-Sign": signature,
        }
        data = {"nonce": nonce, "checksum": checksum, "payload": payload}
        try:
            response = requests.post(URL_API_BITWYRE + uri_path, headers=headers, data=data, timeout=TIMEOUT)
        except requests.exceptions.Timeout as e:
            _module_logger.debug(e)
            (status_code, results) = return_timeout()
            return (status_code, results)

        if response.status_code != 200:
            _module_logger.debug(f"Error {response.reason}, please check again your request")
            (status_code, results) = return_not_ok(response)
            return (status_code, results)

        _module_logger.debug("Successfully create new order")
        results = response.json()
        status_code = 200
        return (status_code, results)

    def cancelling_open_order_per_orderids(self, order_ids: list, qtys: list=[], cancel_all: bool=True) -> (int, dict):
        if not isinstance(order_ids, list):
            _module_logger.debug("Your order ids not a list")
            status_code = 422
            result = {}
            result["error"] = ["Your order ids not a list"]
            result["result"] = {}
            return (status_code, result)
        uri_path = URI_PRIVATE_API_BITWYRE.get("CANCEL_ORDER")
        if cancel_all:
            qtys = [-1] * len(order_ids)
        if len(order_ids) != len(qtys):
            _module_logger.debug("Specify the same number of orders with quantities to ammend/cancel")
            sys.exit(1)
        payload = {"order_ids": order_ids, "qtys": qtys}
        payload = json.dumps(payload)
        (nonce, checksum, signature) = sign(self.secret_key, uri_path, payload)
        headers = {"API-Key": self.api_key, "API-Sign": signature}
        params = {"nonce": nonce, "checksum": checksum, "payload": payload}
        try:
            response = requests.delete(URL_API_BITWYRE + uri_path, headers=headers, params=params, timeout=TIMEOUT)
        except requests.exceptions.Timeout as e:
            _module_logger.debug(e)
            (status_code, results) = return_timeout()
            return (status_code, results)

        if response.status_code != 200:
            _module_logger.debug(f"Error {response.reason}, please check again your request")
            (status_code, results) = return_not_ok(response)
            return (status_code, results)

        _module_logger.debug("Successfully create new order")
        results = response.json()
        status_code = 200
        return (status_code, results)

    def cancelling_open_order_per_instrument(self, instrument: str) -> (int, dict):
        uri_path = URI_PRIVATE_API_BITWYRE.get("CANCEL_ORDER") + "/" + "instrument" + "/" + instrument
        payload = ""
        (nonce, checksum, signature) = sign(self.secret_key, uri_path, payload)
        headers = {"API-Key": self.api_key, "API-Sign": signature}
        params = {"nonce": nonce, "checksum": checksum, "payload": payload}
        try:
            response = requests.delete(URL_API_BITWYRE + uri_path, headers=headers, params=params, timeout=TIMEOUT)
        except requests.exceptions.Timeout as e:
            _module_logger.debug(e)
            (status_code, results) = return_timeout()
            return (status_code, results)

        if response.status_code != 200:
            _module_logger.debug(f"Error {response.reason}, please check again your request")
            (status_code, results) = return_not_ok(response)
            return (status_code, results)

        _module_logger.debug("Successfully create new order")
        results = response.json()
        status_code = 200
        return (status_code, results)
