import {
  getAnnouncements,
  getAssetPairs,
  getAssets,
  getDepth,
  getMarkets,
  getProducts,
  getServerTime,
  getTicker,
  getTrades,
} from '../src';
import * as dotenv from 'dotenv';

dotenv.config({ path: `${__dirname}/../.env` });

describe('Public API Tests', () => {
  global.console = {
    ...console,
    log: jest.fn(),
    debug: jest.fn(),
    info: jest.fn(),
    warn: jest.fn(),
    error: jest.fn(),
  };

  const BASE_URL = process.env.BASE_URL ?? '';

  it('get server time should return', async () => {
    // Arrange

    // Act
    const res = await getServerTime(BASE_URL);

    // Assert
    expect(res.status).toEqual(200);
    expect(res.data.error.length).toEqual(0);
  }, 2000);

  it('get asset pairs should return', async () => {
    // Arrange

    // Act
    const res = await getAssetPairs(BASE_URL, 'market', 'product', 'country');

    // Assert
    expect(res.status).toEqual(200);
    expect(res.data.error.length).toEqual(0);
  }, 2000);

  it('get ticker should return', async () => {
    // Arrange

    // Act
    const res = await getTicker(BASE_URL, 'btc_idr_spot');

    // Assert
    expect(res.status).toEqual(200);
    expect(res.data.error.length).toEqual(0);
  }, 2000);

  it('get trades should return', async () => {
    // Arrange

    // Act
    const res = await getTrades(BASE_URL, 1, 'btc_idr_spot');

    // Assert
    expect(res.status).toEqual(200);
    expect(res.data.error.length).toEqual(0);
  }, 2000);

  it('get depth should return', async () => {
    // Arrange

    // Act
    const res = await getDepth(BASE_URL, 'btc_idr_spot', 1);

    // Assert
    expect(res.status).toEqual(200);
    expect(res.data.error.length).toEqual(0);
  }, 2000);

  it('get assets should return', async () => {
    // Arrange

    // Act
    const res = await getAssets(BASE_URL);

    // Assert
    expect(res.status).toEqual(200);
    expect(res.data.error.length).toEqual(0);
  }, 2000);

  it('get markets should return', async () => {
    // Arrange

    // Act
    const res = await getMarkets(BASE_URL);

    // Assert
    expect(res.status).toEqual(200);
    expect(res.data.error.length).toEqual(0);
  }, 2000);

  it('get products should return', async () => {
    // Arrange

    // Act
    const res = await getProducts(BASE_URL);

    // Assert
    expect(res.status).toEqual(200);
    expect(res.data.error.length).toEqual(0);
  }, 2000);

  it('get announcements should return', async () => {
    // Arrange

    // Act
    const res = await getAnnouncements(BASE_URL);

    // Assert
    expect(res.status).toEqual(200);
    expect(res.data.error.length).toEqual(0);
  }, 2000);
});
