import pytest


@pytest.fixture
def mock_account_balance():
    results = {
        "error": [],
        "result": [
            {
                "asset": "btc",
                "available_balance": 3.973,
                "btc_equivalent": 1,
                "local_equivalent": 0,
                "local_reference": "",
                "total_balance": 4.994,
            },
            {
                "asset": "usd",
                "available_balance": 0,
                "btc_equivalent": 0,
                "local_equivalent": 0,
                "local_reference": "",
                "total_balance": 7000,
            },
            {
                "asset": "idr",
                "available_balance": 100000000,
                "btc_equivalent": 0,
                "local_equivalent": 0,
                "local_reference": "",
                "total_balance": 100000000,
            },
        ],
    }
    return results


@pytest.fixture
def mock_account_statements():
    results = {
        "error": [],
        "withdrawal": {
            "idr": [
                {
                    "id": "26a13a32-2e11-472a-84cc-242d765a88de",
                    "status": "pending",
                    "type": "fiat",
                    "provider": "duitku",
                    "gross_amount": "2000000",
                    "fee": "1500",
                    "nett_amount": "1998500",
                    "submit_time": 1571747594573320135,
                    "success_time": 0,
                }
            ],
            "btc": [
                {
                    "id": "073ba6e5-24d2-4532-8b02-58c1d7a104be",
                    "tx_id": "b84b7839978d53eeb3ee887c238b70933b9ee20c054f71edaee5dbf67fbd3c2a",
                    "status": "success",
                    "type": "crypto",
                    "provider": "hot",
                    "gross_amount": "150.00",
                    "fee": "0.1",
                    "nett_amount": "149.9",
                    "network_confirmation": 4,
                    "submit_time": 1571747594573320135,
                    "success_time": 1571747594573320135,
                }
            ],
        },
        "deposit": {
            "idr": [
                {
                    "id": "f3086a0e-6d25-4590-b47e-a5917816281b",
                    "status": "success",
                    "type": "fiat",
                    "provider": "dana",
                    "gross_amount": "1000000",
                    "fee": "1500",
                    "nett_amount": "995000",
                    "submit_time": 1571747594573320135,
                    "success_time": 1571747594573320135,
                }
            ],
            "btc": [
                {
                    "id": "4b6dc35a-ab03-4f55-bb81-8efb5a8569e0",
                    "tx_id": "f4184fc596403b9d638783cf57adfe4c75c605f6356fbc91338530e9831e9e16",
                    "status": "success",
                    "type": "crypto",
                    "provider": "warm",
                    "gross_amount": "150.00",
                    "fee": "0.1",
                    "nett_amount": "149.9",
                    "network_confirmation": 4,
                    "submit_time": 1571747594573320135,
                    "success_time": 1571747594573320135,
                }
            ],
        },
    }
    return results


@pytest.fixture
def mock_transaction_histories():
    results = {
        "error": [],
        "result": {
            "withdrawal": {
                "idr": [
                    {
                        "id": "26a13a32-2e11-472a-84cc-242d765a88de",
                        "status": "pending",
                        "type": "fiat",
                        "provider": "duitku",
                        "gross_amount": "2000000",
                        "fee": "1500",
                        "nett_amount": "1998500",
                        "submit_time": 1571747594573320135,
                        "success_time": 0,
                    }
                ],
                "btc": [
                    {
                        "id": "073ba6e5-24d2-4532-8b02-58c1d7a104be",
                        "tx_id": "b84b7839978d53eeb3ee887c238b70933b9ee20c054f71edaee5dbf67fbd3c2a",
                        "status": "success",
                        "type": "crypto",
                        "provider": "hot",
                        "gross_amount": "150.00",
                        "fee": "0.1",
                        "nett_amount": "149.9",
                        "network_confirmation": 4,
                        "submit_time": 1571747594573320135,
                        "success_time": 1571747594573320135,
                    }
                ],
            },
            "deposit": {
                "idr": [
                    {
                        "id": "f3086a0e-6d25-4590-b47e-a5917816281b",
                        "status": "success",
                        "type": "fiat",
                        "provider": "dana",
                        "gross_amount": "1000000",
                        "fee": "1500",
                        "nett_amount": "995000",
                        "submit_time": 1571747594573320135,
                        "success_time": 1571747594573320135,
                    }
                ],
                "btc": [
                    {
                        "id": "4b6dc35a-ab03-4f55-bb81-8efb5a8569e0",
                        "tx_id": "f4184fc596403b9d638783cf57adfe4c75c605f6356fbc91338530e9831e9e16",
                        "status": "success",
                        "type": "crypto",
                        "provider": "warm",
                        "gross_amount": "150.00",
                        "fee": "0.1",
                        "nett_amount": "149.9",
                        "network_confirmation": 4,
                        "submit_time": 1571747594573320135,
                        "success_time": 1571747594573320135,
                    }
                ],
            },
            "clearing": {
                "idr": [
                    {
                        "id": "f3086a0e-6d25-4590-b47e-a5917816281b",
                        "status": "success",
                        "type": "spot clearing",
                        "provider": "BTC IDR spot clearing",
                        "gross_amount": "1000000",
                        "fee": "1500",
                        "nett_amount": "995000",
                        "submit_time": 1571747594573320135,
                        "success_time": 1571747594573320135,
                    }
                ],
                "btc": [
                    {
                        "id": "f3086a0e-6d25-4590-b47e-a5917816281b",
                        "status": "success",
                        "type": "spot clearing",
                        "provider": "BTC IDR spot clearing",
                        "gross_amount": "1",
                        "fee": "0.022",
                        "nett_amount": "0.978",
                        "submit_time": 1571747594573320135,
                        "success_time": 1571747594573320135,
                    }
                ],
            },
        },
    }
    return results


@pytest.fixture
def mock_get_open_orders():
    results = {
        "error": [],
        "result": {
            "btc_usd_spot": [
                {
                    "orderid": "97a2387d-5eed-4001-a5eb-67e0e0671645",
                    "origclid": "97a2387d-5eed-4001-a5eb-67e0e0671645",
                    "execid": "ef799ba7-755f-45fb-8a12-6812489869b3",
                    "exectype": 15,
                    "ordstatus": 1,
                    "account": "redacted",
                    "instrument": "btc_usd_futures",
                    "side": 1,
                    "transacttime": 1574230320958860499,
                    "orderqty": "2.9301",
                    "timestamp": 1574174854272296196,
                    "ordtype": 4,
                    "price": "9800.5",
                    "stoppx": "9750",
                    "leavesqty": "1.9301",
                    "cumqty": "1",
                    "LastLiquidityInd": "0.871",
                    "LastPx": "9765",
                    "LastQty": "1",
                    "AvgPx": "9765",
                }
            ]
        },
    }
    return results


@pytest.fixture
def mock_get_closed_orders():
    results = {
        "error": [],
        "result": {
            "orderid": "732f066e-feed-baad-beef-e000ed83243a",
            "origclid": "732f066e-feed-baad-beef-e000ed83243a",
            "execid": "71605de8-efa4-4e20-bcfb-5f23d90f26c2",
            "ordstatusReqID": "3064760e-a92d-4b60-bf9c-a241b36c134a",
            "exectype": 10,
            "ordstatus": 10,
            "account": "redacted",
            "instrument": "btc_usd_spot",
            "side": 1,
            "transacttime": 1574232727730188710,
            "orderqty": "2.9301",
            "timestamp": 1574174854272003795,
            "ordtype": 2,
            "price": "9800.5",
            "leavesqty": "2.9301",
            "cumqty": "0",
        },
    }
    return results


@pytest.fixture
def mock_get_order_info():
    results = {
        "error": [],
        "result": {
            "orderid": "732f066e-feed-baad-beef-e000ed83243a",
            "origclid": "732f066e-feed-baad-beef-e000ed83243a",
            "execid": "71605de8-efa4-4e20-bcfb-5f23d90f26c2",
            "ordstatusReqID": "3064760e-a92d-4b60-bf9c-a241b36c134a",
            "exectype": 10,
            "ordstatus": 10,
            "account": "redacted",
            "instrument": "btc_usd_spot",
            "side": 1,
            "transacttime": 1574232727730188710,
            "orderqty": "2.9301",
            "timestamp": 1574174854272003795,
            "ordtype": 2,
            "price": "9800.5",
            "leavesqty": "2.9301",
            "cumqty": "0",
        },
    }
    return results


@pytest.fixture
def mock_get_trade_history():
    results = {
        "error": [],
        "result": {
            "btc_usd_futures": [
                {
                    "orderid": "97a2387d-5eed-4001-a5eb-67e0e0671645",
                    "origclid": "97a2387d-5eed-4001-a5eb-67e0e0671645",
                    "execid": "ef799ba7-755f-45fb-8a12-6812489869b3",
                    "exectype": 15,
                    "ordstatus": 1,
                    "account": "redacted",
                    "instrument": "btc_usd_futures",
                    "side": 1,
                    "transacttime": 1574230320958860499,
                    "orderqty": "2.9301",
                    "timestamp": 1574174854272296196,
                    "ordtype": 4,
                    "price": "9800.5",
                    "stoppx": "9750",
                    "leavesqty": "1.9301",
                    "cumqty": "1",
                    "LastLiquidityInd": "0.871",
                    "LastPx": "9765",
                    "LastQty": "1",
                    "AvgPx": "9765",
                },
                {
                    "orderid": "97a2387d-5eed-4001-a5eb-67e0e0671645",
                    "origclid": "97a2387d-5eed-4001-a5eb-67e0e0671645",
                    "execid": "ef799ba7-755f-45fb-8a12-6812489869b3",
                    "exectype": 15,
                    "ordstatus": 2,
                    "account": "redacted",
                    "instrument": "btc_usd_futures",
                    "side": 1,
                    "transacttime": 1574230320958860499,
                    "orderqty": "2.9301",
                    "timestamp": 1574174854272296196,
                    "ordtype": 4,
                    "price": "10000.5",
                    "stoppx": "3000",
                    "leavesqty": "1.9301",
                    "cumqty": "2",
                    "LastLiquidityInd": "0.871",
                    "LastPx": "10000",
                    "LastQty": "1",
                    "AvgPx": "10000",
                },
            ]
        },
    }
    return results


@pytest.fixture
def mock_opening_new_order():
    results = {
        "error": [],
        "result": {
            "orderid": "350f9a1f-beea-41ab-87a1-836933113da0",
            "origclid": "350f9a1f-beea-41ab-87a1-836933113da0",
            "execid": "6e3ef058-22b6-41e3-adf7-0ac2b77dd4b4",
            "exectype": 0,
            "ordstatus": 0,
            "account": "redacted",
            "instrument": "btc_usd_spot",
            "side": 2,
            "transacttime": 1574174854271852988,
            "orderqty": "2.9301",
            "timestamp": 1574174854271852988,
            "ordtype": 1,
            "leavesqty": "2.9301",
            "cumqty": "0",
        },
    }
    return results


@pytest.fixture
def mock_cancelling_open_order():
    results = {
        "error": [],
        "result": {
            "orderid": "bae77ef8-5799-465f-8491-ec0eebc2d057",
            "origclid": "31911e87-b547-480f-b8d1-4515529ca2fd",
            "execid": "097b645d-6ff4-435a-a5a4-40c38115b6e9",
            "exectype": 6,
            "ordstatus": 6,
            "account": "redacted",
            "instrument": "btc_usd_spot",
            "side": 2,
            "transacttime": 1574233086281019485,
            "orderqty": "2.9301",
            "timestamp": 1574174854272148294,
            "ordtype": 3,
            "stoppx": "9850.35",
            "leavesqty": "2.9301",
            "cumqty": "0",
        },
    }
    return results
