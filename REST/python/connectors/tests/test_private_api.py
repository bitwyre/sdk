from bitwyre_sdk import PrivateAPI


API_SECRET = "TGU1Hxvz-LcQD2m6c_pBY0HHMVM"
API_KEY = "VYq6yrTK3xw0RL-jX162YC1VwG_t6UrUP_L3Tv49"


def test_account_balances(mocker, mock_account_balance):
    magic_mock = mocker.patch("bitwyre_sdk.requests.get")
    magic_mock.return_value.status_code = 200
    magic_mock.return_value.json.return_value = mock_account_balance
    private_api = PrivateAPI(API_SECRET, API_KEY)
    (status_code, results) = private_api.get_account_balance()
    assert status_code == 200
    assert results == mock_account_balance


def test_account_statements(mocker, mock_account_statements):
    magic_mock = mocker.patch("bitwyre_sdk.requests.get")
    magic_mock.return_value.status_code = 200
    magic_mock.return_value.json.return_value = mock_account_statements
    private_api = PrivateAPI(API_SECRET, API_KEY)
    (status_code, results) = private_api.get_account_statement()
    assert status_code == 200
    assert results == mock_account_statements


def test_transaction_histories(mocker, mock_transaction_histories):
    magic_mock = mocker.patch("bitwyre_sdk.requests.get")
    magic_mock.return_value.status_code = 200
    magic_mock.return_value.json.return_value = mock_transaction_histories
    private_api = PrivateAPI(API_SECRET, API_KEY)
    (status_code, results) = private_api.get_account_statement()
    assert status_code == 200
    assert results == mock_transaction_histories


def test_get_open_orders(mocker, mock_get_open_orders):
    magic_mock = mocker.patch("bitwyre_sdk.requests.get")
    magic_mock.return_value.status_code = 200
    magic_mock.return_value.json.return_value = mock_get_open_orders
    private_api = PrivateAPI(API_SECRET, API_KEY)
    (status_code, results) = private_api.get_open_orders("somecoin", 10, 100)
    assert status_code == 200
    assert results == mock_get_open_orders


def test_get_closed_orders(mocker, mock_get_closed_orders):
    magic_mock = mocker.patch("bitwyre_sdk.requests.get")
    magic_mock.return_value.status_code = 200
    magic_mock.return_value.json.return_value = mock_get_closed_orders
    private_api = PrivateAPI(API_SECRET, API_KEY)
    (status_code, results) = private_api.get_closed_orders("somecoin", 10, 100)
    assert status_code == 200
    assert results == mock_get_closed_orders


def test_get_order_info(mocker, mock_get_order_info):
    magic_mock = mocker.patch("bitwyre_sdk.requests.get")
    magic_mock.return_value.status_code = 200
    magic_mock.return_value.json.return_value = mock_get_order_info
    private_api = PrivateAPI(API_SECRET, API_KEY)
    (status_code, results) = private_api.get_order_info("someid")
    assert status_code == 200
    assert results == mock_get_order_info


def test_get_trade_history(mocker, mock_get_trade_history):
    magic_mock = mocker.patch("bitwyre_sdk.requests.get")
    magic_mock.return_value.status_code = 200
    magic_mock.return_value.json.return_value = mock_get_trade_history
    private_api = PrivateAPI(API_SECRET, API_KEY)
    (status_code, results) = private_api.get_trade_history("someid")
    assert status_code == 200
    assert results == mock_get_trade_history


def test_opening_new_order(mocker, mock_opening_new_order):
    magic_mock = mocker.patch("bitwyre_sdk.requests.post")
    magic_mock.return_value.status_code = 200
    magic_mock.return_value.json.return_value = mock_opening_new_order
    private_api = PrivateAPI(API_SECRET, API_KEY)
    (status_code, results) = private_api.opening_new_order("btc_usd_spot", 1, 1.5, 2, 3)
    assert status_code == 200
    assert results == mock_opening_new_order


def test_opening_new_order_market(mocker, mock_opening_new_order):
    magic_mock = mocker.patch("bitwyre_sdk.requests.post")
    magic_mock.return_value.status_code = 200
    magic_mock.return_value.json.return_value = mock_opening_new_order
    private_api = PrivateAPI(API_SECRET, API_KEY)
    (status_code, results) = private_api.opening_new_order("btc_usd_spot", 1, None, 1, 3)
    assert status_code == 200
    assert results == mock_opening_new_order


def test_opening_new_order_failed_limit_price_null(mocker, mock_opening_new_order):
    magic_mock = mocker.patch("bitwyre_sdk.requests.post")
    magic_mock.return_value.status_code = 200
    magic_mock.return_value.json.return_value = mock_opening_new_order
    private_api = PrivateAPI(API_SECRET, API_KEY)
    (status_code, results) = private_api.opening_new_order("btc_usd_spot", 1, None, 2, 3)
    assert status_code == 422
    assert results == {"error": ["Limit order price cannot be null"], "result": {}}


def test_cancelling_open_order(mocker, mock_cancelling_open_order):
    magic_mock = mocker.patch("bitwyre_sdk.requests.delete")
    magic_mock.return_value.status_code = 200
    magic_mock.return_value.json.return_value = mock_cancelling_open_order
    private_api = PrivateAPI(API_SECRET, API_KEY)
    (status_code, results) = private_api.cancelling_open_order(["0d80b8e5-ebdf-4d7b-8cec-e082b5fbd7dd"])
    assert status_code == 200
    assert results == mock_cancelling_open_order
