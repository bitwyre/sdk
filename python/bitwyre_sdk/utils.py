import hmac
import json
import time
from hashlib import sha256, sha512
import logging


logging.basicConfig(level=logging.DEBUG, format="%(asctime)s:%(levelname)s:%(message)s")


class Logger():

    def __init__(self):
        pass

    def debug(self, text: str):
        logging.debug(f"{text}")

    def info(self, text: str):
        logging.info(f"{text}")

    def warning(self, text: str):
        logging.warning(f"{text}")


def return_timeout():
    status_code = 408
    results = {}
    results["error"] = ["Timeout"]
    results["result"] = {}
    return (status_code, results)


def return_not_ok(response):
    results = {}
    try:
        results = response.json()
        status_code = response.status_code
    except Exception:
        results["error"] = [response.reason]
        results["result"] = {}
        status_code = response.status_code
        return (status_code, results)

    return (status_code, results)


def sign(secret_key: str, uri_path: str, payload: str) -> (int, str, str):
    nonce = time.time_ns()
    payload = json.dumps(payload)
    payload = json.dumps(payload)
    checksum = sha256(str(payload).encode("utf-8")).hexdigest()
    nonce_checksum = sha256(str(nonce).encode("utf-8") + str(checksum).encode("utf-8")).hexdigest()
    signature = hmac.new(
        secret_key.encode("utf-8"), uri_path.encode("utf-8") + nonce_checksum.encode("utf-8"), sha512
    ).hexdigest()
    return (nonce, checksum, signature)
