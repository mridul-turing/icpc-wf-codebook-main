/**
 * Author: tamajitbuba
 * Description: 
 */
struct xor_basis {
	static constexpr int MAXN = 505;
	array<pair<bitset<MAXN>, bitset<MAXN>>, MAXN> basis;
	bool insert(bitset<MAXN> a, int ind){
		bitset<MAXN> cur; cur[ind] = 1;
		per(i, 0, MAXN)
			if (a[i]) {
				if (basis[i].F.any())
					a ^= basis[i].F, cur ^= basis[i].S;
				else {
					basis[i].F = a, basis[i].S = cur;
					return true;
				}
			} 
		return false;
	}
	// insert stores min range to achieve that val
	// if (lb[i].val[j] == 0) {
	//	   lb[i].val[j] = tmp, lb[i].pos[j] = po;
	//	   break;
	// } else {
	//	   if (po > lb[i].pos[j])
	//		   swap(tmp,lb[i].val[j]),
	//		   swap(po,lb[i].pos[j]);
	//	   tmp ^= lb[i].val[j];
	// }
	bool belongs(bitset<MAXN> a, bitset<MAXN> &swit){
		per(i, 0, MAXN)
			if (a[i]) {
				if (basis[i].S != 0)
					a ^= basis[i].F, swit ^= basis[i].S;
				else return false;
			}
		return true;
	}
};
