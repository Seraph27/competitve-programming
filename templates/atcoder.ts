const fs = require("fs");

const input = fs.readFileSync(0, "utf8").trim().split(/\s+/);
let ptr = 0;

const next = (): string => input[ptr++];
const nextInt = (): number => Number(next());

function main(): void {
}

main();

/*
Basic TypeScript cheat sheet

Input
const s = next();
const x = nextInt();
const big = BigInt(next());

const n = nextInt();
const a: number[] = Array.from({ length: n }, () => nextInt());
const grid: number[][] = Array.from(
  { length: n },
  () => Array.from({ length: m }, () => nextInt()),
);

Use this instead when line breaks matter:
const lines = fs.readFileSync(0, "utf8").trim().split("\n");

Arrays
const a: number[] = [];
a.push(x);
a.pop();
const copy = a.slice();
const last = a.at(-1);
const sum = a.reduce((total, x) => total + x, 0);
a.sort((x, y) => x - y);       // ascending numbers
a.sort((x, y) => y - x);       // descending numbers
a.reverse();

Avoid Array(n).fill([]), since every row would be the same array:
const grid = Array.from({ length: n }, () => Array<number>(m).fill(0));

Loops
for(let i = 0; i < n; i++) {
}

for(const x of a) {
}

for(const [i, x] of a.entries()) {
}

Pairs and tuples
type Pair = [number, number];
const p: Pair = [x, y];
const pairs: Pair[] = [];
pairs.sort((a, b) => a[0] - b[0] || a[1] - b[1]);

Set and Map
const seen = new Set<number>();
seen.add(x);
seen.has(x);
seen.delete(x);

const freq = new Map<number, number>();
freq.set(x, (freq.get(x) ?? 0) + 1);
for(const [key, count] of freq) {
}

Strings
const chars = [...s];
const reversed = [...s].reverse().join("");
const parts = s.split("");
const value = Number(s);
const text = String(x);

Math
const low = Math.min(x, y);
const high = Math.max(x, y);
const absolute = Math.abs(x);
const down = Math.floor(x / y);
const up = Math.ceil(x / y);
const mod = ((x % m) + m) % m;
const inf = Number.POSITIVE_INFINITY;

Do not spread a huge array into Math.min or Math.max. Use a loop or reduce:
const minimum = a.reduce((best, x) => Math.min(best, x), Infinity);

Queue in O(1) per removal
const queue: number[] = [start];
let head = 0;
while(head < queue.length) {
  const u = queue[head++];
  queue.push(u);
}

Graph, converting one-indexed vertices to zero-indexed
const adj: number[][] = Array.from({ length: n }, () => []);
const u = nextInt() - 1;
const v = nextInt() - 1;
adj[u].push(v);
adj[v].push(u);

Lower bound, first index with a[i] >= target
function lowerBound(a: number[], target: number): number {
  let L = 0;
  let R = a.length;
  while(L < R) {
    const mid = Math.floor((L + R) / 2);
    if(a[mid] >= target) R = mid;
    else L = mid + 1;
  }
  return L;
}

BigInt, use it above Number.MAX_SAFE_INTEGER (2^53 - 1)
const MOD = 998244353n;
const a = BigInt(next());
const b = 2n;
const answer = (a + b) % MOD;
console.log(answer.toString());
Do not mix number and bigint in the same arithmetic expression.

Output
console.log(answer);
console.log(a.join(" "));
console.log(answers.join("\n"));
*/
