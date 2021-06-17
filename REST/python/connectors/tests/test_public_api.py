from bitwyre_sdk import PublicAPI


def test_servertime(mocker):
    magic_mock = mocker.patch("bitwyre_sdk.requests.get")
    magic_mock.return_value.status_code = 200
    magic_mock.return_value.json.return_value = {"error": [], "result": {"unixtime": 1671744594571020435}}
    public_api = PublicAPI()
    (status_code, results) = public_api.get_server_time()
    assert status_code == 200
    assert isinstance(results, dict)


def test_asset_pairs_success(mocker):
    magic_mock = mocker.patch("bitwyre_sdk.requests.get")
    magic_mock.return_value.status_code = 200
    magic_mock.return_value.json.return_value = {
        "error": [],
        "result": [
            {"instrument": "btc_idr_spot", "symbol": "BTC/IDR"},
            {"instrument": "btc_USD_spot", "symbol": "BTC/USD"},
        ],
    }
    public_api = PublicAPI()
    (status_code, results) = public_api.get_asset_pairs(market="crypto", product="spot", country="ID")
    assert status_code == 200
    assert isinstance(results, dict)


def test_ticker(mocker):
    magic_mock = mocker.patch("bitwyre_sdk.requests.get")
    magic_mock.return_value.status_code = 200
    magic_mock.return_value.json.return_value = {}
    public_api = PublicAPI()
    (status_code, results) = public_api.get_ticker(instrument="btc_usd_spot")
    assert status_code == 200
    assert isinstance(results, dict)


def test_trades(mocker):
    magic_mock = mocker.patch("bitwyre_sdk.requests.get")
    magic_mock.return_value.status_code = 200
    magic_mock.return_value.json.return_value = {}
    public_api = PublicAPI()
    (status_code, results) = public_api.get_trades(instrument="btc_usd_spot", trade_num=2)
    assert status_code == 200
    assert isinstance(results, dict)


def test_depth(mocker):
    magic_mock = mocker.patch("bitwyre_sdk.requests.get")
    magic_mock.return_value.status_code = 200
    magic_mock.return_value.json.return_value = {
        "error": [],
        "result": [
            {
                "instrument": "btc_usd_spot",
                "price": "9000",
                "volume": "2",
                "value": "18000",
                "side": 2,
                "id": "a911b7c0-e431-424f-9f05-49a8ef0c7d93",
                "timestamp": 1571744594571020435,
            },
            {
                "instrument": "btc_usd_spot",
                "price": "9100",
                "volume": "2.1",
                "value": "19110",
                "side": 1,
                "id": "da11b7c0-e3d1-31fe-aaff-bc77ef357ed7",
                "timestamp": 1571747594573320135,
            },
        ],
    }
    public_api = PublicAPI()
    (status_code, results) = public_api.get_depth(instrument="btc_usd_spot", depth_num=2)
    assert status_code == 200
    assert isinstance(results, dict)


def test_announcement(mocker):
    magic_mock = mocker.patch("bitwyre_sdk.requests.get")
    magic_mock.return_value.status_code = 200
    magic_mock.return_value.json.return_value = {
        "error": [],
        "result": {"unixtime": 1571744594571020435, "announcement": "halting btc_usdt_spot"},
    }
    public_api = PublicAPI()
    (status_code, results) = public_api.get_announcements()
    assert status_code == 200
    assert isinstance(results, dict)


def test_asset(mocker):
    magic_mock = mocker.patch("bitwyre_sdk.requests.get")
    magic_mock.return_value.status_code = 200
    magic_mock.return_value.json.return_value = {
        "error": [],
        "result": [
            {
                "asset": "btc",
                "name": "Bitcoin",
                "icon_url": "https://cdn.bitwyre.com/public/images/coins/raster/BTC_500px.png",
                "precision": "1e-8",
                "local_equivalent": "",
                "local_reference": "",
                "btc_equivalent": 1,
                "max_withdrawal": "10",
                "min_withdrawal": "0.001",
                "withdrawal_fee": "0.00000001",
                "deposit_enabled": True,
                "withdrawal_enabled": True,
                "trading_enabled": True,
            },
            {
                "asset": "idr",
                "name": "Indonesian Rupiah",
                "icon_url": "https://cdn.bitwyre.com/public/images/fiats/raster/idr.png",
                "precision": "1",
                "local_equivalent": "",
                "local_reference": "",
                "btc_equivalent": 1,
                "max_withdrawal": "",
                "min_withdrawal": "20000",
                "withdrawal_fee": "10000",
                "deposit_enabled": True,
                "withdrawal_enabled": True,
                "trading_enabled": True,
            },
        ],
    }
    public_api = PublicAPI()
    (status_code, results) = public_api.get_assets()
    assert status_code == 200
    assert isinstance(results, dict)


def test_market(mocker):
    magic_mock = mocker.patch("bitwyre_sdk.requests.get")
    magic_mock.return_value.status_code = 200
    magic_mock.return_value.json.return_value = {"error": [], "result": ["crypto"]}
    public_api = PublicAPI()
    (status_code, results) = public_api.get_markets()
    assert status_code == 200
    assert isinstance(results, dict)


def test_product(mocker):
    magic_mock = mocker.patch("bitwyre_sdk.requests.get")
    magic_mock.return_value.status_code = 200
    magic_mock.return_value.json.return_value = {"error": [], "result": ["spot"]}
    public_api = PublicAPI()
    (status_code, results) = public_api.get_products()
    assert status_code == 200
    assert isinstance(results, dict)
