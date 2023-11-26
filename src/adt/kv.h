struct node {
	void *child[2];
	u32 byte;
	u8 otherbits;
};

static inline void *
walk(uchar *p, uchar *s, usize n)
{
	struct node *q;
	int direction;
	uchar c;
	while ((uintptr)p & 1) {
		q = (void *)(p - 1);
		c = (n > q->byte) ? s[q->byte] : 0;
		direction = (1 + (q->otherbits | c)) >> 8;
		p = q->child[direction];
	}
	return p;
}
