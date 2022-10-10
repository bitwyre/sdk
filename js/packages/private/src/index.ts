import axios from 'axios';
import { sign } from './authentication';
import { SignData, Instruments, currentDateNs } from './types';

async function _get(
  baseUrl: string,
  apiKey: string,
  secretKey: string,
  uriPath: string,
  payload: string,
  params: any = {},
) {
  const signData: SignData = await sign(baseUrl, secretKey, uriPath, payload);

  return await axios.get(uriPath, {
    baseURL: baseUrl,
    params: {
      nonce: signData.nonce,
      checksum: signData.checksum,
      payload,
      ...params,
    },
    headers: {
      'API-Key': apiKey,
      'API-Sign': signData.signature,
    },
  });
}

async function _post(baseUrl: string, apiKey: string, secretKey: string, uriPath: string, payload: any) {
  const payloadString = JSON.stringify(payload);
  const signData: SignData = await sign(baseUrl, secretKey, uriPath, payloadString);

  return await axios.post(
    uriPath,
    {
      nonce: signData.nonce,
      checksum: signData.checksum,
      payload,
    },
    {
      baseURL: baseUrl,
      headers: {
        'API-Key': apiKey,
        'API-Sign': signData.signature,
      },
    },
  );
}

async function _delete(baseUrl: string, apiKey: string, secretKey: string, uriPath: string, payload: string) {
  const signData: SignData = await sign(baseUrl, secretKey, uriPath, payload);

  return await axios.delete(uriPath, {
    baseURL: baseUrl,
    params: {
      nonce: signData.nonce,
      checksum: signData.checksum,
      payload,
    },
    headers: {
      'API-Key': apiKey,
      'API-Sign': signData.signature,
    },
  });
}

export async function getAccountBalance(
  baseUrl: string,
  apiKey: string,
  secretKey: string,
  page: number = 1,
  perPage: number = 10,
  usePagination: boolean = false,
  asset: string = '',
) {
  const payload = '';
  const uriPath: string = '/private/account/spotbalance';

  return await _get(baseUrl, apiKey, secretKey, uriPath, payload, {
    page,
    per_page: perPage,
    use_pagination: usePagination,
    asset,
  });
}

export async function getAccountStatement(baseUrl: string, apiKey: string, secretKey: string) {
  const payload = '';
  const uriPath: string = '/private/account/statement';

  return await _get(baseUrl, apiKey, secretKey, uriPath, payload);
}

export async function getTransactionHistories(baseUrl: string, apiKey: string, secretKey: string) {
  const payload = '';
  const uriPath: string = '/private/account/transactions';

  return await _get(baseUrl, apiKey, secretKey, uriPath, payload);
}

export async function getOpenOrders(
  baseUrl: string,
  apiKey: string,
  secretKey: string,
  instrument: Instruments = 'btc_usdt_spot',
  fromTime: number = 0,
  toTime: number = currentDateNs,
) {
  const payload = JSON.stringify({
    instrument,
    from_time: fromTime,
    to_time: toTime,
  });
  const uriPath: string = '/private/orders/open';

  return await _get(baseUrl, apiKey, secretKey, uriPath, payload);
}

export async function getClosedOrders(
  baseUrl: string,
  apiKey: string,
  secretKey: string,
  instrument: Instruments = 'btc_usdt_spot',
  fromTime: number = 0,
  toTime: number = currentDateNs,
) {
  const payload = JSON.stringify({
    instrument,
    from_time: fromTime,
    to_time: toTime,
  });
  const uriPath: string = '/private/orders/closed';

  return await _get(baseUrl, apiKey, secretKey, uriPath, payload);
}

export async function getOrderInfo(baseUrl: string, apiKey: string, secretKey: string, orderId: string) {
  const payload = JSON.stringify({
    order_id: orderId,
  });
  const uriPath: string = '/private/orders/info';

  return await _get(baseUrl, apiKey, secretKey, uriPath, payload);
}

export async function getTradeHistory(
  baseUrl: string,
  apiKey: string,
  secretKey: string,
  instrument: Instruments = 'btc_usdt_spot',
  count: number = 1,
  fromTime: number = 0,
  toTime: number = currentDateNs,
) {
  const payload = JSON.stringify({
    instrument,
    count,
    from_time: fromTime,
    to_time: toTime,
  });
  const uriPath: string = '/private/trades';

  return await _get(baseUrl, apiKey, secretKey, uriPath, payload);
}

export async function cancellingOpenOrderPerInstrument(
  baseUrl: string,
  apiKey: string,
  secretKey: string,
  instrument: Instruments = 'btc_usdt_spot',
) {
  const payload = JSON.stringify({
    instrument,
  });
  const uriPath: string = '/private/orders/cancel';

  return await _delete(baseUrl, apiKey, secretKey, uriPath, payload);
}

export async function cancellingOpenOrderPerOrderIds(
  baseUrl: string,
  apiKey: string,
  secretKey: string,
  orderIds: string[],
  qtys: number[],
) {
  const payload = JSON.stringify({
    order_ids: orderIds,
    qtys,
  });
  const uriPath: string = '/private/orders/cancel';

  return await _delete(baseUrl, apiKey, secretKey, uriPath, payload);
}

export async function openingNewOrder(
  baseUrl: string,
  apiKey: string,
  secretKey: string,
  instrument: Instruments,
  side: number,
  orderType: number,
  orderQuantity: number,
  price?: number,
) {
  if (orderType === 1) {
    price = 0;
  }
  if (orderType === 2 && price == null) {
    throw new Error('Limit order price cannot be null');
  }

  const uriPath: string = '/private/orders';

  return await _post(baseUrl, apiKey, secretKey, uriPath, {
    instrument,
    side,
    ordtype: orderType,
    orderqty: `${orderQuantity}`,
  });
}

export * from './types';
export * from './authentication';
export * from '@bitwyre/internal-public';
