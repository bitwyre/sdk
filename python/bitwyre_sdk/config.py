TIMEOUT = 5


URL_API_BITWYRE = "https://api.bitwyre.id"

URI_PUBLIC_API_BITWYRE = {
    "SERVERTIME": "/public/time",
    "TRADES": "/public/trades",
    "TICKER": "/public/ticker",
    "INSTRUMENT": "/public/pairs",
    "DEPTH": "/public/depth",
    "ANNOUNCEMENTS": "/public/announcements",
    "PRODUCTS": "/public/products",
    "MARKETS": "/public/markets",
    "ASSETS": "/public/assets",
}
URI_PRIVATE_API_BITWYRE = {
    "ACCOUNT_BALANCE": "/private/account/spotbalance",
    "ACCOUNT_STATEMENT": "/private/account/statement",
    "TRANSACTION_HISTORIES": "/private/account/transactions",
    "ORDER": "/private/orders",
    "CANCEL_ORDER": "/private/orders/cancel",
    "OPEN_ORDERS": "/private/orders/open",
    "CLOSED_ORDERS": "/private/orders/closed",
    "ORDER_INFO": "/private/orders/info",
    "TRADE_HISTORY": "/private/trades",
}
