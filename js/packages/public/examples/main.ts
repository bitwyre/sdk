import { getServerTime } from '..';

async function main() {
  const res = await getServerTime(`https://api.bitwyre.com`);
  return res.data;
}

main()
  .then(console.log)
  .catch((e) => console.log(e.response.data));
