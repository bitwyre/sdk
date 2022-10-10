import {
  cancellingOpenOrderPerInstrument,
  getAccountBalance,
  getClosedOrders,
  getOpenOrders,
  getOrderInfo,
  getTradeHistory,
  getTransactionHistories,
  openingNewOrder,
} from '../src';
import * as dotenv from 'dotenv';

dotenv.config({ path: `${__dirname}/../.env` });

describe('Private API Tests', () => {
  global.console = {
    ...console,
    log: jest.fn(),
    debug: jest.fn(),
    info: jest.fn(),
    warn: jest.fn(),
    error: jest.fn(),
  };

  const BASE_URL = process.env.BASE_URL ?? '';
  const API_KEY = process.env.API_KEY ?? '';
  const SECRET_KEY = process.env.SECRET_KEY ?? '';

  it('get account balance should return', async () => {
    // Arrange

    // Act
    const res = await getAccountBalance(BASE_URL, API_KEY, SECRET_KEY);

    // Assert
    expect(res.status).toEqual(200);
    expect(res.data.error.length).toEqual(0);
  }, 6000);

  it('get transaction histories should return', async () => {
    // Arrange

    // Act
    const res = await getTransactionHistories(BASE_URL, API_KEY, SECRET_KEY);

    // Assert
    expect(res.status).toEqual(200);
    expect(res.data.error.length).toEqual(0);
  }, 6000);

  it('get open orders should return', async () => {
    // Arrange

    // Act
    const res = await getOpenOrders(BASE_URL, API_KEY, SECRET_KEY);

    // Assert
    expect(res.status).toEqual(200);
    expect(res.data.error.length).toEqual(0);
  }, 6000);

  it('get closed orders should return', async () => {
    // Arrange

    // Act
    const res = await getClosedOrders(BASE_URL, API_KEY, SECRET_KEY);

    // Assert
    expect(res.status).toEqual(200);
    expect(res.data.error.length).toEqual(0);
  }, 6000);

  it('get trade history should return', async () => {
    // Arrange

    // Act
    const res = await getTradeHistory(BASE_URL, API_KEY, SECRET_KEY);

    // Assert
    expect(res.status).toEqual(200);
    expect(res.data.error.length).toEqual(0);
  }, 6000);
});
