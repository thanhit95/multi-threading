const { createHash } = await import('node:crypto');


export const getHash = (numLoops, str) => {
  for (let i = numLoops; i > 0; --i) {
    str = createHash('sha256').update(str).digest('hex');
  }
  return str;
};


export const splitStrInToChunks = (numChunks, str) => {
  const lstChunks = [];
  const quotient = Math.floor(str.length / numChunks);
  const remainder = str.length % numChunks;
  for (let i = 0; i < numChunks; ++i) {
    const chunk = str.substring(
      i * quotient + Math.min(i, remainder),
      (i+1) * quotient + Math.min(i+1, remainder)
    );
    lstChunks.push(chunk);
  }
  return lstChunks;
};
