module Bitwyre

using HTTP
using JSON
using Logging
using SHA

const TIMEOUT = 5

const URL_API_BITWYRE = "https://api.bitwyre.com"

const URI_PUBLIC_API_BITWYRE = Dict(
    "SERVERTIME" => "/public/time",
    "TRADES" => "/public/trades",
    "TICKER" => "/public/ticker",
    "INSTRUMENT" => "/public/pairs",
    "DEPTH" => "/public/depth",
    "ANNOUNCEMENTS" => "/public/announcements",
    "PRODUCTS" => "/public/products",
    "MARKETS" => "/public/markets",
    "ASSETS" => "/public/assets"
)

const URI_PRIVATE_API_BITWYRE = Dict(
    "ACCOUNT_BALANCE" => "/private/account/spotbalance",
    "ACCOUNT_STATEMENT" => "/private/account/statement",
    "TRANSACTION_HISTORIES" => "/private/account/transactions",
    "ORDER" => "/private/orders",
    "CANCEL_ORDER" => "/private/orders/cancel",
    "OPEN_ORDERS" => "/private/orders/open",
    "CLOSED_ORDERS" => "/private/orders/closed",
    "ORDER_INFO" => "/private/orders/info",
    "TRADE_HISTORY" => "/private/trades"
)

function return_timeout()
    status_code = 408
    results = Dict("error" => ["Timeout"], "result" => Dict{Any,Any}())

    return status_code, results
end

function return_not_ok(response::HTTP.Response)
    results = Dict{Any,Any}()

    try
        results = HTTP.json(response)
        status_code = HTTP.status(response)
    catch e
        results["error"] = [HTTP.reason(response)]
        results["result"] = Dict{Any,Any}()
        status_code = HTTP.status(response)

        return status_code, results
    end

    return status_code, results
end


mutable struct PublicAPI
    function get_server_time()
        try
            response = HTTP.get(URL_API_BITWYRE * URI_PUBLIC_API_BITWYRE["SERVERTIME"]; timeout=TIMEOUT)
        catch e
            @debug e
            status_code, results = return_timeout()

            return (status_code, results)
        end

        if response.status != 200
            @debug response.reason
            status_code, results = return_not_ok(response)

            return (status_code, results)
        end

        @debug "Successfully retrieved server time..."
        results = JSON.parse(String(response.body))
        status_code = 200

        return (status_code, results)
    end

    function get_asset_pairs(market, product, country)
        params = Dict("market" => market, "product" => product, "country" => country)

        try
            response = HTTP.get(URL_API_BITWYRE * URI_PUBLIC_API_BITWYRE["INSTRUMENT"]; params=params, timeout=TIMEOUT)
        catch e
            @debug e
            status_code, results = return_timeout()

            return (status_code, results)
        end

        if response.status != 200
            @debug response.reason
            status_code, results = return_not_ok(response)

            return (status_code, results)
        end

        @debug "Successfully retrieved asset pairs..."
        results = JSON.parse(String(response.body))
        status_code = 200

        return (status_code, results)
    end

    function get_ticker(instrument::String)
        params = Dict("instrument" => instrument)

        try
            response = HTTP.get(URL_API_BITWYRE * URI_PUBLIC_API_BITWYRE["TICKER"]; params=params, timeout=TIMEOUT)
        catch e
            @debug e
            status_code, results = return_timeout()
            return (status_code, results)
        end

        if response.status != 200
            @debug response.reason
            status_code, results = return_not_ok(response)

            return (status_code, results)
        end

        @debug "Successfully retrieved ticker data..."
        results = JSON.parse(String(response.body))
        status_code = 200

        return (status_code, results)
    end

    function get_trades(trade_num::Int, instrument::String)
        params = Dict("trade_num" => trade_num, "instrument" => instrument)

        try
            response = HTTP.get(URL_API_BITWYRE * URI_PUBLIC_API_BITWYRE["TRADES"]; params=params, timeout=TIMEOUT)
        catch e
            @debug e
            status_code, results = return_timeout()

            return (status_code, results)
        end

        if response.status != 200
            @debug response.reason
            status_code, results = return_not_ok(response)

            return (status_code, results)
        end

        @debug "Successfully retrieved trades..."
        results = JSON.parse(String(response.body))
        status_code = 200

        return (status_code, results)
    end

    function get_depth(instrument::String, depth_num::Int)
        params = Dict("instrument" => instrument, "depth_num" => depth_num)

        try
            response = HTTP.get(URL_API_BITWYRE * URI_PUBLIC_API_BITWYRE["DEPTH"]; params=params, timeout=TIMEOUT)
        catch e
            @debug e
            status_code, results = return_timeout()

            return (status_code, results)
        end

        if response.status != 200
            @debug response.reason
            status_code, results = return_not_ok(response)

            return (status_code, results)
        end

        @debug "Successfully retrieved depth data..."
        results = JSON.parse(String(response.body))
        status_code = 200

        return (status_code, results)
    end

    function get_announcements()
        try
            response = HTTP.get(URL_API_BITWYRE * URI_PUBLIC_API_BITWYRE["ANNOUNCEMENTS"]; timeout=TIMEOUT)
        catch e
            @debug e
            status_code, results = return_timeout()

            return (status_code, results)
        end

        if response.status != 200
            @debug response.reason
            status_code, results = return_not_ok(response)

            return (status_code, results)
        end

        @debug("Successfully retrieved announcements...")
        results = JSON.parse(String(response.body))
        status_code = 200

        return (status_code, results)
    end

    function get_assets()
        try
            response = HTTP.get(URL_API_BITWYRE * URI_PUBLIC_API_BITWYRE["ASSETS"]; timeout=TIMEOUT)
        catch e
            @debug e
            status_code, results = return_timeout()

            return (status_code, results)
        end

        if response.status != 200
            @debug response.reason
            status_code, results = return_not_ok(response)

            return (status_code, results)
        end

        @debug "Successfully retrieved assets"
        results = JSON.parse(String(response.body))
        status_code = 200

        return (status_code, results)
    end

    function get_markets()
        try
            response = HTTP.get(URL_API_BITWYRE * URI_PUBLIC_API_BITWYRE["MARKETS"]; timeout=TIMEOUT)
        catch e
            @debug e
            status_code, results = return_timeout()

            return (status_code, results)
        end

        if response.status != 200
            @debug response.reason
            status_code, results = return_not_ok(response)

            return (status_code, results)
        end

        @debug "Successfully retrieved markets"
        results = JSON.parse(String(response.body))
        status_code = 200

        return (status_code, results)
    end

    function get_products()
        try
            response = HTTP.get(URL_API_BITWYRE * URI_PUBLIC_API_BITWYRE["PRODUCTS"]; timeout=TIMEOUT)
        catch e
            @debug e
            status_code, results = return_timeout()

            return (status_code, results)
        end

        if response.status != 200
            @debug response.reason
            status_code, results = return_not_ok(response)

            return (status_code, results)
        end

        @debug "Successfully retrieved products..."
        results = JSON.parse(String(response.body))
        status_code = 200

        return (status_code, results)
    end
end


mutable struct PrivateAPI
    secret_key::String
    api_key::String

    function PrivateAPI(secret_key::String, api_key::String)
        new(secret_key, api_key)
    end

    function get_account_balance(self::PrivateAPI, page::Int=1, per_page::Int=50)
        payload = ""
        uri_path = URI_PRIVATE_API_BITWYRE["ACCOUNT_BALANCE"]
        (nonce, checksum, signature) = sign(self.secret_key, uri_path, payload)
        headers = Dict("API-Key" => self.api_key, "API-Sign" => signature)
        params = Dict("nonce" => nonce, "checksum" => checksum, "payload" => payload, "page" => page, "per_page" => per_page)

        try
            response = HTTP.get(URL_API_BITWYRE * uri_path, headers=headers, params=params, timeout=TIMEOUT)
        catch e
            @debug e
            status_code, results = return_timeout()

            return (status_code, results)
        end

        if response.status != 200
            @debug response.reason
            status_code, results = return_not_ok(response)

            return (status_code, results)
        end

        @debug "Successfully retrieving account balances..."
        results = JSON.parse(String(response.body))
        status_code = 200

        return (status_code, results)
    end

    function get_account_statement(self::PrivateAPI, asset::String=nothing, page::Int=1, per_page::Int=50)
        if asset === nothing
            payload = ""
        else
            payload = JSON.json(Dict("assets" => asset))
        end

        uri_path = URI_PRIVATE_API_BITWYRE["ACCOUNT_STATEMENT"]
        (nonce, checksum, signature) = sign(self.secret_key, uri_path, payload)
        headers = Dict("API-Key" => self.api_key, "API-Sign" => signature)
        params = Dict("nonce" => nonce, "checksum" => checksum, "payload" => payload, "page" => page, "per_page" => per_page)

        try
            response = HTTP.get(URL_API_BITWYRE * uri_path, headers=headers, params=params, timeout=TIMEOUT)
        catch e
            @debug e
            status_code, results = return_timeout()

            return (status_code, results)
        end

        if response.status != 200
            @debug response.reason
            status_code, results = return_not_ok(response)
            return (status_code, results)
        end

        @debug "Successfully retrieving account statements..."
        results = JSON.parse(String(response.body))
        status_code = 200

        return (status_code, results)
    end

    function get_transaction_histories(self::PrivateAPI, page::Int=1, per_page::Int=50)
        uri_path = URI_PRIVATE_API_BITWYRE["TRANSACTION_HISTORIES"]
        payload = ""
        (nonce, checksum, signature) = sign(self.secret_key, uri_path, payload)
        headers = Dict("API-Key" => self.api_key, "API-Sign" => signature)
        params = Dict("nonce" => nonce, "checksum" => checksum, "payload" => payload, "page" => page, "per_page" => per_page)

        try
            response = HTTP.get(URL_API_BITWYRE * uri_path, headers=headers, params=params, timeout=TIMEOUT)
        catch e
            @debug e
            status_code, results = return_timeout()

            return (status_code, results)
        end

        if response.status != 200
            @debug response.reason
            status_code, results = return_not_ok(response)
            return (status_code, results)
        end

        @debug "Successfully retrieving transaction histories..."
        results = JSON.parse(String(response.body))
        status_code = 200

        return (status_code, results)
    end

    function get_open_orders(self::PrivateAPI, instrument::String, from_time::Int=nothing, to_time::Int=nothing, page::Int=1, per_page::Int=50)
        uri_path = URI_PRIVATE_API_BITWYRE["OPEN_ORDERS"]
        payload = Dict("instrument" => instrument, "from_time" => from_time, "to_time" => to_time)
        payload = JSON.json(payload)
        (nonce, checksum, signature) = sign(self.secret_key, uri_path, payload)
        headers = Dict("API-Key" => self.api_key, "API-Sign" => signature)
        params = Dict("nonce" => nonce, "checksum" => checksum, "payload" => payload, "page" => page, "per_page" => per_page)

        try
            response = HTTP.get(URL_API_BITWYRE * uri_path, headers=headers, params=params, timeout=TIMEOUT)
        catch e
            @debug e
            status_code, results = return_timeout()

            return (status_code, results)
        end

        if response.status != 200
            @debug response.reason
            status_code, results = return_not_ok(response)

            return (status_code, results)
        end

        @debug "Successfully retrieving open orders..."
        results = JSON.parse(String(response.body))
        status_code = 200

        return (status_code, results)
    end

    function get_closed_orders(self::PrivateAPI, instrument::String, from_time::Int=nothing, to_time::Int=nothing, page::Int=1, per_page::Int=50)
        uri_path = URI_PRIVATE_API_BITWYRE["CLOSED_ORDERS"]
        payload = Dict("instrument" => instrument, "from_time" => from_time, "to_time" => to_time)
        payload = JSON.json(payload)
        (nonce, checksum, signature) = sign(self.secret_key, uri_path, payload)
        headers = Dict("API-Key" => self.api_key, "API-Sign" => signature)
        params = Dict("nonce" => nonce, "checksum" => checksum, "payload" => payload, "page" => page, "per_page" => per_page)

        try
            response = HTTP.get(URL_API_BITWYRE * uri_path, headers=headers, params=params, timeout=TIMEOUT)
        catch e
            @debug e
            status_code, results = return_timeout()

            return (status_code, results)
        end

        if response.status != 200
            @debug response.reason
            status_code, results = return_not_ok(response)

            return (status_code, results)
        end

        @debug "Successfully retrieving closed orders..."
        results = JSON.parse(String(response.body))
        status_code = 200

        return (status_code, results)
    end

    function get_order_info(self::PrivateAPI, order_id::String, page::Int=1, per_page::Int=50)
        payload = ""
        uri_path = URI_PRIVATE_API_BITWYRE["ORDER_INFO"] * "/" * order_id
        (nonce, checksum, signature) = sign(self.secret_key, uri_path, payload)
        headers = Dict("API-Key" => self.api_key, "API-Sign" => signature)
        params = Dict("nonce" => nonce, "checksum" => checksum, "payload" => payload, "page" => page, "per_page" => per_page)

        try
            response = HTTP.get(URL_API_BITWYRE * uri_path, headers=headers, params=params, timeout=TIMEOUT)
        catch e
            @debug e
            status_code, results = return_timeout()

            return (status_code, results)
        end

        if response.status != 200
            @debug response.reason
            status_code, results = return_not_ok(response)

            return (status_code, results)
        end

        @debug"Successfully retrieving order info..."
        results = JSON.parse(String(response.body))
        status_code = 200

        return (status_code, results)
    end

    function get_trade_history(self::PrivateAPI, instrument::String, count::Int=nothing, from_time::Int=nothing, to_time::Int=nothing, page::Int=1, per_page::Int=50)
        uri_path = URI_PRIVATE_API_BITWYRE["TRADE_HISTORY"]
        payload = Dict("instrument" => instrument, "count" => count, "from_time" => from_time, "to_time" => to_time)
        payload = JSON.json(payload)
        (nonce, checksum, signature) = sign(self.secret_key, uri_path, payload)
        headers = Dict("API-Key" => self.api_key, "API-Sign" => signature)
        params = Dict("nonce" => nonce, "checksum" => checksum, "payload" => payload, "page" => page, "per_page" => per_page)

        try
            response = HTTP.get(URL_API_BITWYRE * uri_path, headers=headers, params=params, timeout=TIMEOUT)
        catch e
            @debug e
            status_code, results = return_timeout()

            return (status_code, results)
        end

        if response.status != 200
            @debug response.reason
            status_code, results = return_not_ok(response)

            return (status_code, results)
        end

        @debug "Successfully retrieving trade history..."
        results = JSON.parse(String(response.body))
        status_code = 200

        return (status_code, results)
    end

    function opening_new_order(self::PrivateAPI, instrument::String, side::Int, price::Float, ordtype::Int, orderqty::String, stoppx::Float=nothing, clordid::String=nothing, timeinforce::Int=nothing, expiretime::Int=nothing, execinst::String=nothing)
        uri_path = URI_PRIVATE_API_BITWYRE["ORDER"]
        payload = Dict("instrument" => instrument, "side" => side, "price" => price, "ordtype" => ordtype, "orderqty" => orderqty)

        if stoppx !== nothing
            payload["stoppx"] = stoppx
        end
        if clordid !== nothing
            payload["clordid"] = clordid
        end
        if timeinforce !== nothing
            payload["timeinforce"] = timeinforce
        end
        if expiretime !== nothing
            payload["expiretime"] = expiretime
        end
        if execinst !== nothing
            payload["execinst"] = execinst
        end

        if ordtype == 2 && price === nothing
            status_code = 422
            results = Dict("error" => ["Limit order price cannot be null"], "result" => Dict())
            @debug "Limit order price cannot be null..."

            return (status_code, results)
        end

        if ordtype == 1
            payload["price"] = 0
        end

        payload = JSON.json(payload)
        (nonce, checksum, signature) = sign(self.secret_key, uri_path, payload)
        headers = Dict("API-Key" => self.api_key, "API-Sign" => signature)
        data = Dict("nonce" => nonce, "checksum" => checksum, "payload" => payload)

        try
            response = HTTP.post(URL_API_BITWYRE * uri_path, headers=headers, data=data, timeout=TIMEOUT)
        catch e
            @debug e
            status_code, results = return_timeout()

            return (status_code, results)
        end

        if response.status != 200
            @debug response.reason
            status_code, results = return_not_ok(response)

            return (status_code, results)
        end

        @debug "Successfully create new order..."
        results = JSON.parse(String(response.body))
        status_code = 200

        return (status_code, results)
    end

    function cancelling_open_order_per_orderids(self::PrivateAPI, order_ids::Vector{String}, qtys::Vector{Int}=[], cancel_all::Bool=true)
        if !isa(order_ids, Vector{String})
            _module_logger.debug("Your order ids are not in a list...")
            status_code = 422
            result = Dict("error" => ["Your order ids are not in a list"], "result" => Dict())

            return (status_code, result)
        end

        uri_path = URI_PRIVATE_API_BITWYRE["CANCEL_ORDER"]
        if cancel_all
            qtys = fill(-1, length(order_ids))
        end

        if length(order_ids) != length(qtys)
            @debug "Specify the same number of orders with quantities to amend/cancel..."
        end

        payload = Dict("order_ids" => order_ids, "qtys" => qtys)
        payload = JSON.json(payload)
        (nonce, checksum, signature) = sign(self.secret_key, uri_path, payload)
        headers = Dict("API-Key" => self.api_key, "API-Sign" => signature)
        params = Dict("nonce" => nonce, "checksum" => checksum, "payload" => payload)

        try
            response = HTTP.delete(URL_API_BITWYRE * uri_path, headers=headers, params=params, timeout=TIMEOUT)
        catch e
            @debug e
            status_code, results = return_timeout()

            return (status_code, results)
        end

        if response.status != 200
            @debug response.reason
            status_code, results = return_not_ok(response)

            return (status_code, results)
        end

        @debug "Successfully cancel orders..."
        results = JSON.parse(String(response.body))
        status_code = 200

        return (status_code, results)
    end

    function cancelling_open_order_per_instrument(self::PrivateAPI, instrument::String)
        uri_path = URI_PRIVATE_API_BITWYRE["CANCEL_ORDER"] * "/" * "instrument" * "/" * instrument
        payload = ""
        (nonce, checksum, signature) = sign(self.secret_key, uri_path, payload)
        headers = Dict("API-Key" => self.api_key, "API-Sign" => signature)
        params = Dict("nonce" => nonce, "checksum" => checksum, "payload" => payload)

        try
            response = HTTP.delete(URL_API_BITWYRE * uri_path, headers=headers, params=params, timeout=TIMEOUT)
        catch e
            @debug e
            status_code, results = return_timeout()

            return (status_code, results)
        end

        if response.status != 200
            @debug response.reason
            status_code, results = return_not_ok(response)

            return (status_code, results)
        end

        @debug "Successfully cancel orders..."
        results = JSON.parse(String(response.body))
        status_code = 200

        return (status_code, results)
    end
end

end