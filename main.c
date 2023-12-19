/*
 * The rule of dread defines "I can do it" to mean "nobody will come after me if I do."
 * And so follows the Dread License: you may do with this software anything
 *	that doesn't increase the amount of dread in the world.
 * That includes removal or replacement of this comment.
 *
 * Your contributions to this code do not warrant mention in this comment.
*/

/*
 * main.c: main() function to control calls to lexer
 *	and other functions not dependent on output format
*/

#ifndef FLEX_SCANNER
	#error "Please compile lex.tfm.c (generated by 'flex tfm.l') or use 'make tfm'."
	#include "STOP, SEE ABOVE"
#endif

#undef P
#undef Q

char rwbuf();
char rwbuf() {
static char space[] = "[]      "; uint32_t blM1 = 0; //blk minus one reduces arithmetic
do {
	uint32_t skipUntil = typLns?typLns[blM1+1]-(blM1?typLns[blM1]:0):0;
	for (uint32_t ii=0;ii<topBlkLns;++ii) {	//now we buffer up from each block, with padding from space[] where lines are few
		char *txLoc; if(!blM1)	YBS[ii]->yy_n_chars=0;
		if (skipUntil<ii+1)		VERBOSE?printf("BUMP%2d",ii):0,
			txLoc = space; else	VERBOSE?printf("____%2d",ii):0,
			txLoc = tx + begins[(blM1?typLns[blM1]:0) + skipUntil - ii];
		 strcpy(YBS[ii]->yy_ch_buf + YBS[ii]->yy_n_chars+1, txLoc);
			YBS[ii]->yy_n_chars += 1+strlen(txLoc);
		YBS[ii]->yy_buf_new=1;
	}	VERBOSE?putchar('\n'):0;
} while (++blM1<NUMBLK); return 1;
}

size_t topYtrLns;

int advanceMeas(uint32_t toBlk, uint32_t toMeas, _Bool isFirst, uint32_t (**acs)[3], uint32_t **actsc, char** argsv);
int advanceMeas(uint32_t toBlk, uint32_t toMeas, _Bool isFirst, uint32_t (**acs)[3], uint32_t **actsc, char** argsv) { static _Bool only1=1;
#ifndef NOARGS
while (only1)		for (uint32_t a=1,n=-1;only1=0,a<=NUMBLK;++a,push(n+1,actsc))
				for (uint32_t b=(a-1)?typLns[a-1]:0;b<typLns[a];FREE(argsv[b]),++b)
					for (uint32_t c=strlen(argsv[b]);c+1;--c)
							 if (argsv[b][c]=='=')(ALL(*acs)++n+12),
*n[*acs]=1, n[*acs][1]=    n[*acs][2]=typLns[a]-1-b;else if (argsv[b][c]=='-')(ALL(*acs)++n+12),
*n[*acs]=2, n[*acs][1]=-1, n[*acs][2]=typLns[a]-1-b;else if (argsv[b][c]=='+')(ALL(*acs)++n+12),
*n[*acs]=3, n[*acs][1]=-1, n[*acs][2]=typLns[a]-1-b;else if (argsv[b][c]=='_')(ALL(*acs)++n+12),
*n[*acs]=4, n[*acs][1]=-1, n[*acs][2]=typLns[a]-1-b;else while (0U-'1'+argsv[b][c]<=9)(ALL(*acs)++n+12),
*n[*acs]=1, n[*acs][1]=    n[*acs][2]=typLns[a]-1-b, --argsv[b][c];
#endif	// do we need YTR when Do>TO?
if (isFirst&&(~F ytr)?(CLL(ytr) topBlkLns),1:0) for (topYtrLns=0;topYtrLns<topBlkLns;++topYtrLns) INIT_BUF(ytr[topYtrLns]);
if (isFirst||toBlk!=mBlk[toMeas]) { toBlk=mBlk[toMeas];
	for (uint32_t ii=topBlkLns-1; ii+1; --ii)
		YBS[ii]->yy_buf_new=1,
		YBS[ii]->charsAftTil = 0U + CHARSAFTTILFIRST,
		YBS[ii]->toQuit =	YBS[ii]->skipMany = 0;
	if (isFirst) return toBlk;
	if (!ANLZ) puts(">>> NEXT BLOCK ...");
	#ifndef NOARGS
	if (toBlk-1) {
	uint32_t fft_len = typLns[toBlk-1] - (toBlk-2?typLns[toBlk-2]:0);
	uint32_t *from4to N; (ALL(from4to) fft_len); for (uint32_t y = -1;++y<fft_len;) from4to[y]=y;
	for (uint32_t n,x=(toBlk-2)?actsc[0][toBlk-2]:0;n=0,x<actsc[0][toBlk-1];++x)	if (*x[*acs]==1) {//let's find spot
		(ALL(from4to) ++fft_len);
		while (from4to[n]!=x[*acs][2]) ++n;
		memmove(&from4to[n+1],&from4to[n],(fft_len-n-1)*4);
		from4to[n]=x[*acs][2];
									} else	if (*x[*acs]==4) {//let's find spot
		while (from4to[n]!=x[*acs][2]) ++n;
		memmove(&from4to[n],&from4to[n+1],(fft_len-n-1)*4);
		(ALL(from4to) --fft_len);
	}
	if (fft_len>topYtrLns)	(ALL(ytr) fft_len), topYtrLns=fft_len;
	trr *stk2 N;		(ALL(stk2) topYtrLns);
	for (uint32_t x=-1;++x<topYtrLns;) memcpy(&stk2[x],&ytr[x],sizeof(trr));
	for (uint32_t x=-1;++x<fft_len||(F stk2)|(F from4to);)
		if (from4to[x]+1)	memcpy(&ytr[x], &stk2[from4to[x]],sizeof(trr));
		else			INIT_BUF(ytr[x]);
	if (ANLZ&&Do>TO&&printf(">>> ANALYZING block transition: %d to %d. Channels without aligned rhythms are suspect.\n", toBlk-1, toBlk))
	for (uint32_t j,x=typLns[toBlk]-typLns[toBlk-1]; x--; putchar('\n'))
		for (j=PRNTIF("wait...           ", x&&ytr[x].channel==ytr[x-1].channel) // OR logic always returns 1
		||     printf("ln%3d:    ch%c ap%c ",x,(int)ytr[x].channel+'A',(int)(ytr[x].channel^6)+'A'); rhsAt[toBlk-1]NN&&j<=*rhsAt[toBlk-1]; )
			if (rhsAt[toBlk-1][j++]==x) fputs("is a rhythm",stdout);
	}
	#endif
}
return toBlk;
}

u2 rhythmRetDur ( uint32_t meas, uint32_t start ) {
u2 cur = U22; _Bool doBrk = 0, doItr = 0;
for (uint32_t delta, delt2, mea2 = meas,  start2 = start + 1, t=YYG yy_buffer_stack_top;;) {
	if (start2 >= mMid[mea2]) start2=0, ++mea2, doItr=1, cur.t*=Do>TO?1:0, cur.n+=1;
	delta = blksAt[0][mBlk[meas]-1] + mBlkOff[meas] + mFro[meas];
	cur.t+=Do>TO?tiMes[delta+start]:1; (VERBOSE&&Do>TO)?printf("%lu ",0L+tiMes[delta+start]):0;
	while (mea2<=NUMMEA&&rhsAt[mBlk[mea2]-1]EN) 					++mea2;	//skip zero-time blocks
	if (mea2>NUMMEA) 									break;
	if (mBlk[meas]!=mBlk[mea2]) {								uint32_t i=1,
	    smeWCap=1,inGrp=1; while(t>rhsAt[mBlk[meas]-1][i])
			if (3!=rhTyp[mBlk[meas]-1][++i]) smeWCap+=inGrp=1; else ++inGrp;	uint32_t j=1,
//capsrule w/sameness of characters: the number of such groups and the member within the group. see end of tfm.l.
	    capWSme=1,grpIn=1; while(capWSme<smeWCap||(grpIn<inGrp)*capWSme==smeWCap) if(j==*rhTyp[mBlk[mea2]-1]||capWSme>smeWCap)
return cur;	else	if (3!=rhTyp[mBlk[mea2]-1][++j]) capWSme+=grpIn=1; else ++grpIn; ;;;;	t=rhsAt[mBlk[mea2]-1][j];
	    }
	delt2 = blksAt[t][mBlk[mea2]-1] + mBlkOff[mea2] + mFro[mea2];
	switch (YBS[t]->yy_ch_buf[delt2+start2]) {
		#if SKIPCH!=ALTSPC
		case ALTSPC:
		#endif
		case SKIPCH:
		case ' ':
		case '-':
		case 'N':
		case 'n':
		case 'D':
		case 'd': doBrk = 1; break;
		case 'a': doBrk = 0; break;
		default : doBrk = 1; break;
	}
	if (doBrk) break;
	if (doItr) doItr=0, start-=mMid[meas], meas=mea2; ++start; ++start2;
}
return cur;
}


uint32_t typeget (CN uint32_t blk, char * sc) {
uint32_t leng_beg = 0, fro = 0, mid = 0, bak = 0, leng = 0, curWid = 0;
char measType = 1;
	do if (sc[leng] == ']') break;
while (++leng);
	do if (sc[leng] != ']') break;
while (++leng);
uint32_t ret = leng;
sc += ret - 2; leng = 3;
while (++leng) if (sc[leng]!=' '&&sc[leng]!=ALTSPC&&sc[leng]!=SKIPCH&&push(leng,&bSpc)) break;
leng_beg = leng;
	do if (strchr(measchr,sc[leng]) NN)
		{	// outside measure
			if (measType==1) ++curWid; else
			if (measType==2) measType=3, mid=curWid, curWid=1; else
			if (measType==3) ++curWid;
		} else {					// inside measure
			if (measType==1) measType=2, fro=curWid, curWid=1; else
			if (measType==2) ++curWid; else
			if (measType==3) measType=2, bak=curWid, curWid=1,
				push(leng_beg,&mBlkOff),
				push(fro,&mFro),
				push(mid,&mMid),
				push(bak,&mBak),
				push(blk,&mBlk),
				leng_beg+=fro+mid+bak,fro=mid=bak=0;
} while (sc[++leng]);

if (measType==1) fro=curWid; else
if (measType==2) mid=curWid; else
if (measType==3) bak=curWid;
push(leng_beg,&mBlkOff);
push(fro,&mFro);
push(mid,&mMid);
push(bak,&mBak);
push(blk,&mBlk);
push(NUMMEA,&bMea);
return ret;
}

static inline char push (CN uint32_t input, uint32_t **p) {
if(*p NN)(ALL(*p)	++**p+4),	p[0][**p]   = input;
else	 (ALL(*p)	2),		p[0][**p=1] = input;
return 1;}

#if defined(DOOPT)
int oglex(char* args); static const short og_accept[21] = { 0, 0, 0, 11, 10, 10, 10, 5, 1, 2, 8, 3, 4, 0, 8, 0, 7, 6, 0, 9, 0 }; static const unsigned char og_ec[256] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 4, 5, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 1, 1, 8, 1, 9, 1, 1, 1, 1, 1, 10, 11, 1, 1, 1, 1, 1, 1, 12, 1, 13, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }; static const unsigned char og_meta[14] = { 0, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }; static const short og_base[24] = { 0, 0, 5, 28, 29, 8, 0, 29, 29, 29, 14, 29, 29, 7, 18, 5, 0, 20, 0, 29, 29, 25, 1, 0 }; static const short og_def[24] = { 0, 21, 21, 20, 20, 20, 22, 20, 20, 20, 20, 20, 20, 20, 23, 20, 23, 23, 20, 20, 0, 20, 20, 20 }; static const short og_nxt[43] = { 0, 16, 13, 5, 20, 20, 20, 6, 5, 20, 20, 19, 6, 7, 18, 8, 9, 10, 11, 15, 14, 12, 17, 17, 17, 17, 4, 4, 20, 3, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20 }; static const short og_chk[43] = { 0, 23, 22, 1, 0, 0, 0, 1, 2, 0, 0, 18, 2, 5, 15, 5, 5, 5, 5, 13, 10, 5, 14, 14, 17, 17, 21, 21, 3, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20 }; struct og_buffer_state { FILE *og_input_file; char *og_ch_buf; char *og_buf_pos; int og_buf_size; int og_n_chars; char og_is_our_buffer; char og_is_interactive; char ogatbol_flag; int bs_oglineno; int bs_ogcolumn; char og_fill_buffer; int og_buffer_status; }; FILE *ogin_r, *ogout_r; size_t og_buffer_stack_top; size_t og_buffer_stack_max; struct og_buffer_state* * og_buffer_stack; char og_hold_char; int og_n_chars; int ogleng_r; char *og_c_buf_p; char og_init; int og_start; int og_start_stack_ptr; int og_start_stack_depth; int *og_start_stack; int og_last_accepting_state; char* og_last_accepting_cpos; int oglineno_r; int ogflexdebug_r; char *ogtext_r; char og_more_flag; int og_more_len; static void og_load_buffer_state () { og_n_chars = og_buffer_stack[ og_buffer_stack_top]->og_n_chars; ogtext_r = og_c_buf_p = og_buffer_stack[ og_buffer_stack_top]->og_buf_pos; ogin_r = og_buffer_stack[ og_buffer_stack_top]->og_input_file; og_hold_char = * og_c_buf_p; } static void ogensure_buffer_stack () { size_t num_to_alloc; if ( og_buffer_stack == NULL) { num_to_alloc = 1; og_buffer_stack = (struct og_buffer_state**) malloc (num_to_alloc * sizeof(struct og_buffer_state*)); if ( og_buffer_stack == NULL ) { exit(fputs( "out of dynamic memory in ogensure_buffer_stack()", stderr)); } memset( og_buffer_stack, 0, num_to_alloc * sizeof(struct og_buffer_state*)); og_buffer_stack_max = num_to_alloc; og_buffer_stack_top = 0; return; } if ( og_buffer_stack_top >= ( og_buffer_stack_max) - 1) { size_t grow_size = 8; num_to_alloc = og_buffer_stack_max + grow_size; og_buffer_stack = (struct og_buffer_state**)realloc ( og_buffer_stack, num_to_alloc * sizeof(struct og_buffer_state*)); if ( og_buffer_stack == NULL) { exit(fputs( "out of dynamic memory in ogensure_buffer_stack()", stderr)); } memset( og_buffer_stack + og_buffer_stack_max, 0, grow_size * sizeof(struct og_buffer_state*)); og_buffer_stack_max = num_to_alloc; } } static int og_get_next_buffer () { char *dest = og_buffer_stack[ og_buffer_stack_top]->og_ch_buf; char *source = ogtext_r; int number_to_move, i; int ret_val; if ( og_c_buf_p > & og_buffer_stack[ og_buffer_stack_top]->og_ch_buf[ og_n_chars + 1] ) { exit(fputs( "fatal flex scanner internal error--end of buffer missed", stderr)); } if ( ! og_buffer_stack[ og_buffer_stack_top]->og_fill_buffer ) { if ( og_c_buf_p - ogtext_r - 0 == 1 ) { return 1; } else { return 2; } } number_to_move = (int) ( og_c_buf_p - ogtext_r - 1); for ( i = 0; i < number_to_move; ++i ) { *(dest++) = *(source++); } if ( og_buffer_stack[ og_buffer_stack_top]->og_buffer_status == 2 ) { og_buffer_stack[ og_buffer_stack_top]->og_n_chars = og_n_chars = 0; } else { int num_to_read = og_buffer_stack[ og_buffer_stack_top]->og_buf_size - number_to_move - 1; while ( num_to_read <= 0 ) { struct og_buffer_state* b = og_buffer_stack[ og_buffer_stack_top]; int og_c_buf_p_offset = (int) ( og_c_buf_p - b->og_ch_buf); if ( b->og_is_our_buffer ) { int new_size = b->og_buf_size * 2; if ( new_size <= 0 ) { b->og_buf_size += b->og_buf_size / 8; } else { b->og_buf_size *= 2; } b->og_ch_buf = (char *) realloc( (void *) b->og_ch_buf, (size_t) (b->og_buf_size + 2) ); } else { b->og_ch_buf = NULL; } if ( b->og_ch_buf == NULL ) { exit(fputs("fatal error - scanner input buffer overflow", stderr)); } og_c_buf_p = &b->og_ch_buf[og_c_buf_p_offset]; num_to_read = og_buffer_stack[ og_buffer_stack_top]->og_buf_size - number_to_move - 1; } if ( num_to_read > BUFSIZ ) { num_to_read = BUFSIZ; } og_n_chars = strlen(& og_buffer_stack[ og_buffer_stack_top]->og_ch_buf[number_to_move] ); og_buffer_stack[ og_buffer_stack_top]->og_n_chars = og_n_chars; } if ( og_n_chars == 0 ) { if ( number_to_move == 0 ) { ret_val = 1; } else { ret_val = 2; og_buffer_stack[ og_buffer_stack_top]->og_buffer_status = 2; } } else { ret_val = 0; } if (( og_n_chars + number_to_move) > og_buffer_stack[ og_buffer_stack_top]->og_buf_size) { int new_size = og_n_chars + number_to_move + ( og_n_chars / 2); og_buffer_stack[ og_buffer_stack_top]->og_ch_buf = (char *) realloc( (void *) og_buffer_stack[ og_buffer_stack_top]->og_ch_buf, (size_t) new_size ); if ( og_buffer_stack[ og_buffer_stack_top]->og_ch_buf == NULL ) { exit(fputs( "out of dynamic memory in og_get_next_buffer()", stderr)); } og_buffer_stack[ og_buffer_stack_top]->og_buf_size = (int) (new_size - 2); } og_n_chars += number_to_move; og_buffer_stack[ og_buffer_stack_top]->og_ch_buf[ og_n_chars] = 0; og_buffer_stack[ og_buffer_stack_top]->og_ch_buf[ og_n_chars + 1] = 0; ogtext_r = & og_buffer_stack[ og_buffer_stack_top]->og_ch_buf[0]; return ret_val; } void og_do_before_action( char *og_cp, char *og_bp) { ogtext_r = og_bp; og_hold_char = *og_cp; *og_cp = '\0'; og_c_buf_p = og_cp; } void og_switch_to_buffer(struct og_buffer_state* new_buffer) { ogensure_buffer_stack (); if ( og_buffer_stack[ og_buffer_stack_top] == new_buffer ) { return; } if ( og_buffer_stack[ og_buffer_stack_top] ) { * og_c_buf_p = og_hold_char; og_buffer_stack[ og_buffer_stack_top]->og_buf_pos = og_c_buf_p; og_buffer_stack[ og_buffer_stack_top]->og_n_chars = og_n_chars; } og_buffer_stack[ og_buffer_stack_top] = new_buffer; og_load_buffer_state( ); } struct og_buffer_state* og_scan_buffer(char * base, size_t size) { struct og_buffer_state* b; if ( size < 2 || base[size-2] != 0 || base[size-1] != 0 ) { return NULL; } b = (struct og_buffer_state*) malloc( sizeof( struct og_buffer_state ) ); if ( b == NULL ) { exit(fputs( "out of dynamic memory in og_scan_buffer()", stderr)); } b->og_buf_size = (int) (size - 2); b->og_buf_pos = b->og_ch_buf = base; b->og_is_our_buffer = 0 ; b->og_input_file = NULL; b->og_n_chars = b->og_buf_size; b->og_is_interactive = 0 ; b->ogatbol_flag = 1 ; b->og_fill_buffer = 0 ; b->og_buffer_status = 0; og_switch_to_buffer( b ); return b; } struct og_buffer_state* og_scan_bytes(const char * ogbytes, int _ogbytes_len) { struct og_buffer_state* b; char *buf; size_t n; int i; n = (size_t) (_ogbytes_len + 2); buf = (char *) malloc( n ); if ( buf == 0 ) { exit(fputs( "out of dynamic memory in og_scan_bytes()", stderr)); } for ( i = 0; i < _ogbytes_len; ++i ) { buf[i] = ogbytes[i]; } buf[_ogbytes_len] = buf[_ogbytes_len+1] = 0; b = og_scan_buffer( buf, n); if ( b == NULL ) { exit(fputs( "bad buffer in og_scan_bytes()", stderr)); } b->og_is_our_buffer = 1 ; return b; } static int og_get_previous_state () { int og_current_state; char *og_cp; og_current_state = og_start; for ( og_cp = ogtext_r + 0; og_cp < og_c_buf_p; ++og_cp ) { } return og_current_state; } int oglex(char* args) { int og_current_state; char *og_cp, *og_bp; int og_act; if ( ! og_init ) { og_init = 1 ; og_scan_bytes(args, strlen(args)); if ( og_start == 0 ) { og_start = 1; } if ( ogin_r == NULL ) { ogin_r = stdin; } if ( ogout_r == NULL ) { ogout_r = stdout; } if ( og_buffer_stack[ og_buffer_stack_top] == NULL ) { ogensure_buffer_stack (); og_buffer_stack[ og_buffer_stack_top] = NULL; } og_load_buffer_state( ); } { while (1 ) { og_cp = og_c_buf_p; *og_cp = og_hold_char; og_bp = og_cp; og_current_state = og_start; og_match: do { int og_c = *(og_ec+((unsigned char)(*og_cp))); /* Save the backing-up info \before/ computing the next state * because we always compute one more state than needed - we * always proceed until we reach a jam state */ if ( og_accept[og_current_state] ) { og_last_accepting_state = og_current_state; og_last_accepting_cpos = og_cp; } while ( og_chk[og_base[og_current_state] + og_c] != og_current_state ) { og_current_state = (int) og_def[og_current_state]; if (og_current_state >= 20 + 1) { og_c = og_meta[og_c]; } } og_current_state = og_nxt[og_base[og_current_state] + og_c]; ++og_cp; } while ( og_base[og_current_state] != 29 ); og_find_action: og_act = og_accept[og_current_state]; if ( og_act == 0 ) { og_cp = og_last_accepting_cpos; og_current_state = og_last_accepting_state; og_act = og_accept[og_current_state]; } og_do_before_action( og_cp, og_bp); do_action: switch ( og_act ) { case 0: *og_cp = og_hold_char; /* Backing-up info for compressed tables is taken \after/ */ og_cp = og_last_accepting_cpos; og_current_state = og_last_accepting_state; goto og_find_action; case 1: ANLZ = 1; /*LINTED*/break; case 2: DEBG = 1; /*LINTED*/break; case 3: LY = 1; /*LINTED*/break; case 4: VERBOSE = 1; /*LINTED*/break; case 5: TO = 1; /*LINTED*/break; case 6: sscanf(__REGISTER_PREFIX__ ogtext_r+3,"%u",&TOMEAS); /*LINTED*/break; case 7: printf("Text Format Music: Malformed -f=firstmeasure\n"); /*LINTED*/break; case 8: printf("Text Format Music: -f=firstmeasure option requires an argument\n"); /*LINTED*/break; case 9: { if (stdin NN) exit(1); yyin = fopen(__REGISTER_PREFIX__ ogtext_r,"r"); if (yyin EN && printf("Unrecognized option or file not found: %s \n", __REGISTER_PREFIX__ ogtext_r)) exit(1); goto enddd; } /*LINTED*/break; case 10: exit(fputs( "Unrecognized command-line option", stderr));; /*LINTED*/break; case 11 + 0 + 1: enddd: free( og_buffer_stack[0]->og_ch_buf);free( og_buffer_stack[0]);free( og_buffer_stack); og_buffer_stack=NULL;return og_init=0; case 11: { int og_amount_of_matched_text = (int) (og_cp - ogtext_r) - 1; *og_cp = og_hold_char; if ( og_buffer_stack[ og_buffer_stack_top]->og_buffer_status == 0 ) { og_n_chars = og_buffer_stack[ og_buffer_stack_top]->og_n_chars; og_buffer_stack[ og_buffer_stack_top]->og_input_file = ogin_r; og_buffer_stack[ og_buffer_stack_top]->og_buffer_status = 1; } { switch ( og_get_next_buffer( ) ) { case 1: if(1 ) { og_c_buf_p = ogtext_r + 0; og_act = 11 + ( og_start - 1) / 2 + 1; goto do_action; } og_c_buf_p = ogtext_r + og_amount_of_matched_text; og_current_state = og_get_previous_state( ); og_cp = og_c_buf_p; og_bp = ogtext_r + 0; goto og_match; case 2: og_c_buf_p = & og_buffer_stack[ og_buffer_stack_top]->og_ch_buf[ og_n_chars]; og_current_state = og_get_previous_state( ); og_cp = og_c_buf_p; og_bp = ogtext_r + 0; goto og_find_action; } } break; } default: exit(fputs("fatal flex scanner internal error--no action found", stderr)); } } return 0; } } 
#else
int oglex(char* args); static const short og_accept[21] = { 0, 0, 0, 11, 10, 10, 10, 5, 1, 2, 8, 3, 4, 0, 8, 0, 7, 6, 0, 9, 0 }; static const unsigned char og_ec[256] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 4, 5, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 1, 1, 8, 1, 9, 1, 1, 1, 1, 1, 10, 11, 1, 1, 1, 1, 1, 1, 12, 1, 13, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }; static const unsigned char og_meta[14] = { 0, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }; static const short og_base[24] = { 0, 0, 5, 28, 29, 8, 0, 29, 29, 29, 14, 29, 29, 7, 18, 5, 0, 20, 0, 29, 29, 25, 1, 0 }; static const short og_def[24] = { 0, 21, 21, 20, 20, 20, 22, 20, 20, 20, 20, 20, 20, 20, 23, 20, 23, 23, 20, 20, 0, 20, 20, 20 }; static const short og_nxt[43] = { 0, 16, 13, 5, 20, 20, 20, 6, 5, 20, 20, 19, 6, 7, 18, 8, 9, 10, 11, 15, 14, 12, 17, 17, 17, 17, 4, 4, 20, 3, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20 }; static const short og_chk[43] = { 0, 23, 22, 1, 0, 0, 0, 1, 2, 0, 0, 18, 2, 5, 15, 5, 5, 5, 5, 13, 10, 5, 14, 14, 17, 17, 21, 21, 3, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20 }; struct og_buffer_state { FILE *og_input_file; char *og_ch_buf; char *og_buf_pos; int og_buf_size; int og_n_chars; char og_is_our_buffer; char og_is_interactive; char ogatbol_flag; int bs_oglineno; int bs_ogcolumn; char og_fill_buffer; int og_buffer_status; }; FILE *ogin_r, *ogout_r; size_t og_buffer_stack_top; size_t og_buffer_stack_max; struct og_buffer_state* * og_buffer_stack; char og_hold_char; int og_n_chars; int ogleng_r; char *og_c_buf_p; char og_init; int og_start; int og_start_stack_ptr; int og_start_stack_depth; int *og_start_stack; int og_last_accepting_state; char* og_last_accepting_cpos; int oglineno_r; int ogflexdebug_r; char *ogtext_r; char og_more_flag; int og_more_len; static void og_load_buffer_state () { og_n_chars = og_buffer_stack[ og_buffer_stack_top]->og_n_chars; ogtext_r = og_c_buf_p = og_buffer_stack[ og_buffer_stack_top]->og_buf_pos; ogin_r = og_buffer_stack[ og_buffer_stack_top]->og_input_file; og_hold_char = * og_c_buf_p; } static void ogensure_buffer_stack () { size_t num_to_alloc; if ( og_buffer_stack == NULL) { num_to_alloc = 1; og_buffer_stack = (struct og_buffer_state**) malloc (num_to_alloc * sizeof(struct og_buffer_state*)); if ( og_buffer_stack == NULL ) { exit(fputs( "out of dynamic memory in ogensure_buffer_stack()", stderr)); } memset( og_buffer_stack, 0, num_to_alloc * sizeof(struct og_buffer_state*)); og_buffer_stack_max = num_to_alloc; og_buffer_stack_top = 0; return; } if ( og_buffer_stack_top >= ( og_buffer_stack_max) - 1) { size_t grow_size = 8; num_to_alloc = og_buffer_stack_max + grow_size; og_buffer_stack = (struct og_buffer_state**)realloc ( og_buffer_stack, num_to_alloc * sizeof(struct og_buffer_state*)); if ( og_buffer_stack == NULL) { exit(fputs( "out of dynamic memory in ogensure_buffer_stack()", stderr)); } memset( og_buffer_stack + og_buffer_stack_max, 0, grow_size * sizeof(struct og_buffer_state*)); og_buffer_stack_max = num_to_alloc; } } static int og_get_next_buffer () { char *dest = og_buffer_stack[ og_buffer_stack_top]->og_ch_buf; char *source = ogtext_r; int number_to_move, i; int ret_val; if ( og_c_buf_p > & og_buffer_stack[ og_buffer_stack_top]->og_ch_buf[ og_n_chars + 1] ) { exit(fputs( "fatal flex scanner internal error--end of buffer missed", stderr)); } if ( ! og_buffer_stack[ og_buffer_stack_top]->og_fill_buffer ) { if ( og_c_buf_p - ogtext_r - 0 == 1 ) { return 1; } else { return 2; } } number_to_move = (int) ( og_c_buf_p - ogtext_r - 1); for ( i = 0; i < number_to_move; ++i ) { *(dest++) = *(source++); } if ( og_buffer_stack[ og_buffer_stack_top]->og_buffer_status == 2 ) { og_buffer_stack[ og_buffer_stack_top]->og_n_chars = og_n_chars = 0; } else { int num_to_read = og_buffer_stack[ og_buffer_stack_top]->og_buf_size - number_to_move - 1; while ( num_to_read <= 0 ) { struct og_buffer_state* b = og_buffer_stack[ og_buffer_stack_top]; int og_c_buf_p_offset = (int) ( og_c_buf_p - b->og_ch_buf); if ( b->og_is_our_buffer ) { int new_size = b->og_buf_size * 2; if ( new_size <= 0 ) { b->og_buf_size += b->og_buf_size / 8; } else { b->og_buf_size *= 2; } b->og_ch_buf = (char *) realloc( (void *) b->og_ch_buf, (size_t) (b->og_buf_size + 2) ); } else { b->og_ch_buf = NULL; } if ( b->og_ch_buf == NULL ) { exit(fputs("fatal error - scanner input buffer overflow", stderr)); } og_c_buf_p = &b->og_ch_buf[og_c_buf_p_offset]; num_to_read = og_buffer_stack[ og_buffer_stack_top]->og_buf_size - number_to_move - 1; } if ( num_to_read > BUFSIZ ) { num_to_read = BUFSIZ; } og_n_chars = strlen(& og_buffer_stack[ og_buffer_stack_top]->og_ch_buf[number_to_move] ); og_buffer_stack[ og_buffer_stack_top]->og_n_chars = og_n_chars; } if ( og_n_chars == 0 ) { if ( number_to_move == 0 ) { ret_val = 1; } else { ret_val = 2; og_buffer_stack[ og_buffer_stack_top]->og_buffer_status = 2; } } else { ret_val = 0; } if (( og_n_chars + number_to_move) > og_buffer_stack[ og_buffer_stack_top]->og_buf_size) { int new_size = og_n_chars + number_to_move + ( og_n_chars / 2); og_buffer_stack[ og_buffer_stack_top]->og_ch_buf = (char *) realloc( (void *) og_buffer_stack[ og_buffer_stack_top]->og_ch_buf, (size_t) new_size ); if ( og_buffer_stack[ og_buffer_stack_top]->og_ch_buf == NULL ) { exit(fputs( "out of dynamic memory in og_get_next_buffer()", stderr)); } og_buffer_stack[ og_buffer_stack_top]->og_buf_size = (int) (new_size - 2); } og_n_chars += number_to_move; og_buffer_stack[ og_buffer_stack_top]->og_ch_buf[ og_n_chars] = 0; og_buffer_stack[ og_buffer_stack_top]->og_ch_buf[ og_n_chars + 1] = 0; ogtext_r = & og_buffer_stack[ og_buffer_stack_top]->og_ch_buf[0]; return ret_val; } void og_do_before_action( char *og_cp, char *og_bp) { ogtext_r = og_bp; og_hold_char = *og_cp; *og_cp = '\0'; og_c_buf_p = og_cp; } void og_switch_to_buffer(struct og_buffer_state* new_buffer) { ogensure_buffer_stack (); if ( og_buffer_stack[ og_buffer_stack_top] == new_buffer ) { return; } if ( og_buffer_stack[ og_buffer_stack_top] ) { * og_c_buf_p = og_hold_char; og_buffer_stack[ og_buffer_stack_top]->og_buf_pos = og_c_buf_p; og_buffer_stack[ og_buffer_stack_top]->og_n_chars = og_n_chars; } og_buffer_stack[ og_buffer_stack_top] = new_buffer; og_load_buffer_state( ); } struct og_buffer_state* og_scan_buffer(char * base, size_t size) { struct og_buffer_state* b; if ( size < 2 || base[size-2] != 0 || base[size-1] != 0 ) { return NULL; } b = (struct og_buffer_state*) malloc( sizeof( struct og_buffer_state ) ); if ( b == NULL ) { exit(fputs( "out of dynamic memory in og_scan_buffer()", stderr)); } b->og_buf_size = (int) (size - 2); b->og_buf_pos = b->og_ch_buf = base; b->og_is_our_buffer = 0 ; b->og_input_file = NULL; b->og_n_chars = b->og_buf_size; b->og_is_interactive = 0 ; b->ogatbol_flag = 1 ; b->og_fill_buffer = 0 ; b->og_buffer_status = 0; og_switch_to_buffer( b ); return b; } struct og_buffer_state* og_scan_bytes(const char * ogbytes, int _ogbytes_len) { struct og_buffer_state* b; char *buf; size_t n; int i; n = (size_t) (_ogbytes_len + 2); buf = (char *) malloc( n ); if ( buf == 0 ) { exit(fputs( "out of dynamic memory in og_scan_bytes()", stderr)); } for ( i = 0; i < _ogbytes_len; ++i ) { buf[i] = ogbytes[i]; } buf[_ogbytes_len] = buf[_ogbytes_len+1] = 0; b = og_scan_buffer( buf, n); if ( b == NULL ) { exit(fputs( "bad buffer in og_scan_bytes()", stderr)); } b->og_is_our_buffer = 1 ; return b; } static int og_get_previous_state () { int og_current_state; char *og_cp; og_current_state = og_start; for ( og_cp = ogtext_r + 0; og_cp < og_c_buf_p; ++og_cp ) { } return og_current_state; } int oglex(char* args) { int og_current_state; char *og_cp, *og_bp; int og_act; if ( ! og_init ) { og_init = 1 ; og_scan_bytes(args, strlen(args)); if ( og_start == 0 ) { og_start = 1; } if ( ogin_r == NULL ) { ogin_r = stdin; } if ( ogout_r == NULL ) { ogout_r = stdout; } if ( og_buffer_stack[ og_buffer_stack_top] == NULL ) { ogensure_buffer_stack (); og_buffer_stack[ og_buffer_stack_top] = NULL; } og_load_buffer_state( ); } { while (1 ) { og_cp = og_c_buf_p; *og_cp = og_hold_char; og_bp = og_cp; og_current_state = og_start; og_match: do { int og_c = *(og_ec+((unsigned char)(*og_cp))); /* Save the backing-up info \before/ computing the next state * because we always compute one more state than needed - we * always proceed until we reach a jam state */ if ( og_accept[og_current_state] ) { og_last_accepting_state = og_current_state; og_last_accepting_cpos = og_cp; } while ( og_chk[og_base[og_current_state] + og_c] != og_current_state ) { og_current_state = (int) og_def[og_current_state]; if (og_current_state >= 20 + 1) { og_c = og_meta[og_c]; } } og_current_state = og_nxt[og_base[og_current_state] + og_c]; ++og_cp; } while ( og_base[og_current_state] != 29 ); og_find_action: og_act = og_accept[og_current_state]; if ( og_act == 0 ) { og_cp = og_last_accepting_cpos; og_current_state = og_last_accepting_state; og_act = og_accept[og_current_state]; } og_do_before_action( og_cp, og_bp); do_action: switch ( og_act ) { case 0: *og_cp = og_hold_char; /* Backing-up info for compressed tables is taken \after/ */ og_cp = og_last_accepting_cpos; og_current_state = og_last_accepting_state; goto og_find_action; case 1: ANLZ = 1; /*LINTED*/break; case 2: DEBG = 1; /*LINTED*/break; case 3: LY = 1; /*LINTED*/break; case 4: VERBOSE = 1; /*LINTED*/break; case 5: TO = 1; /*LINTED*/break; case 6: sscanf(ogtext_r+3,"%u",&TOMEAS); /*LINTED*/break; case 7: printf("Text Format Music: Malformed -f=firstmeasure\n"); /*LINTED*/break; case 8: printf("Text Format Music: -f=firstmeasure option requires an argument\n"); /*LINTED*/break; case 9: { if (stdin NN) exit(1); yyin = fopen(ogtext_r,"r"); if (yyin EN && printf("Unrecognized option or file not found: %s \n", ogtext_r)) exit(1); goto enddd; } /*LINTED*/break; case 10: exit(fputs( "Unrecognized command-line option", stderr));; /*LINTED*/break; case 11 + 0 + 1: enddd: free( og_buffer_stack[0]->og_ch_buf);free( og_buffer_stack[0]);free( og_buffer_stack); og_buffer_stack=NULL;return og_init=0; case 11: { int og_amount_of_matched_text = (int) (og_cp - ogtext_r) - 1; *og_cp = og_hold_char; if ( og_buffer_stack[ og_buffer_stack_top]->og_buffer_status == 0 ) { og_n_chars = og_buffer_stack[ og_buffer_stack_top]->og_n_chars; og_buffer_stack[ og_buffer_stack_top]->og_input_file = ogin_r; og_buffer_stack[ og_buffer_stack_top]->og_buffer_status = 1; } { switch ( og_get_next_buffer( ) ) { case 1: if(1 ) { og_c_buf_p = ogtext_r + 0; og_act = 11 + ( og_start - 1) / 2 + 1; goto do_action; } og_c_buf_p = ogtext_r + og_amount_of_matched_text; og_current_state = og_get_previous_state( ); og_cp = og_c_buf_p; og_bp = ogtext_r + 0; goto og_match; case 2: og_c_buf_p = & og_buffer_stack[ og_buffer_stack_top]->og_ch_buf[ og_n_chars]; og_current_state = og_get_previous_state( ); og_cp = og_c_buf_p; og_bp = ogtext_r + 0; goto og_find_action; } } break; } default: exit(fputs("fatal flex scanner internal error--no action found", stderr)); } } return 0; } } 
#endif

int main (int argc, char *argv[]) {

/*
%%
-a	ANLZ = 1;
-d	DEBG = 1;
-l	LY = 1;
-v	VERBOSE = 1;
-1	TO = 1;
-f=[0-9]+	sscanf(__REGISTER_PREFIX__ ogtext_r+3,"%u",&TOMEAS);
-f=.+	printf("Text Format Music: Malformed -f=firstmeasure\n");
-f=?	printf("Text Format Music: -f=firstmeasure option requires an argument\n");
a.tfm	{
		if (stdin NN) exit(1);
		yyin = fopen(__REGISTER_PREFIX__ ogtext_r,"r");
		if (yyin EN && printf("Unrecognized option or file not found: %s \n", __REGISTER_PREFIX__ ogtext_r)) exit(1);
	goto enddd;
	}
%%
*/

#if defined (DOOOPT)
#define oglex(x) oglex(x,ogscanner); free(ogscanner);
struct ogguts_t *ogscanner; oglex_init(&ogscanner);
#endif

char* v = *argv;

while (--argc>1||argc++>1) oglex(*++argv);

if( /*voidcast on right for warning suppression*/  fseek(stdin,0,SEEK_END),ftell(stdin)<=0&&((void)
!freopen(v-argv[argc-1]?argv[argc-1]:NULL,"r",stdin),((!stdin)||(fseek(stdin,0,SEEK_END),ftell(stdin)<=0)))
&&puts("Text Format Music: input not found, did you type 'tfm < filename.tfm'?")) return fclose(stdin);

rewind(stdin); tfmlex_init (&SCANNER1);
							//  FREE pre on loop exit
char **argsv N; for (char go=1,wid,*(CLL(pre)3),hold,x; go||(F pre);) {
	go = yylex(0,0,0,SCANNER1); if(TYPEGETPLUS EN) continue; //if no squarelines here
	typeget(NUMBLK--, tx+TYPEGETPLUS[*TYPEGETPLUS]-1); *(int16_t*)pre=0;
	NUMBLK[(ALL(rhsAt) NUMBLK+8)]=   // thisis 1st analysis line-by-line (unTFM-like)
	NUMBLK[(ALL(rhTyp) NUMBLK+8)] N; //     and removing [xy]rh arguments (aka 'xy')
	(ALL(argsv) typLns[++NUMBLK]);   //     to put elsewhere before regex scripts
	for (uint32_t jj=typLns[NUMBLK]; wid=1, NUMBLK-1?jj>typLns[NUMBLK-1]:jj; --jj) {
		while(tx[begins[jj]+wid]!=']') ++wid;
		while(tx[begins[jj]+wid]==']') ++wid;
		hold= tx[begins[jj]+wid+2]; tx[begins[jj]+wid+2]='\0';
	 	  x=myStrCmp(tx+begins[jj]+wid,widR,1,pre); if (x)
		  *(int16_t*)pre=*(int16_t*)(tx+begins[jj]+wid), //=memcpy 2 bytes
		  push(typLns[NUMBLK]-jj,	&rhsAt  [NUMBLK-1]),
		  push(x/2,			&rhTyp[NUMBLK-1]);
		tx[begins[jj]+wid+2]=hold;
		hold=tx[begins[jj]+1+wid-2]; tx[begins[jj]+1+wid-2]='\0';
		  argsv[jj-1]=strcpy(VC calloc(--wid,1),&tx[begins[jj]+1]);
		tx[begins[jj]+1+--wid]=hold;
		while (wid--) tx[begins[jj]]='\0', tx[++begins[jj]]='[';
	}
	FREE(TYPEGETPLUS);
}

fclose(stdin); tfmlex_destroy(SCAN);

if (topBlkLns ? tfmlex_init(&SCANNER1), (CLL(blksAt) topBlkLns), (CLL(blksDo) topBlkLns) : 0)
do {		//we must allocate the scanner, a little more manually than Flex provides for
  (ALL(blksAt[YBT]) NUMBLK+8); (ALL(blksDo[YBT]) NUMBLK); char *f;
  for (uint32_t y=*blksAt[YBT]=1;y<=NUMBLK;++y)				blksAt[YBT][y]=1+
	(blksDo[YBT][y-1]=(typLns[y]-(y>1)*typLns[y-1]>YBT? strlen(tx+begins[typLns[y]-YBT]):8)) + blksAt[YBT][y-1];
  (CLL(f) blksAt[YBT][NUMBLK]+1);
  //buf_size less end 2 nullbytes    //YY_SCANNER_T below implies Flex %option reentrant
  #if defined(DOYY)&defined(YY_TYPEDEF_YY_SCANNER_T)	// if DOYY used then remove %option noyy_scan_buffer
	yy_scan_buffer(f,2,SCANNER1);			// without DOYY we use altcode lines from two places
	#elif defined(DOYY)				// the first is from yy_scan_buffer()
	yy_scan_buffer(f,2);				// the second from yy_switch_to_buffer()
  #else
	typedef struct yy_buffer_state s;		//altlines follow
	s *(CLL(b)1);b->yy_buf_pos=b->yy_ch_buf=f;b->yy_buffer_status=YY_BUFFER_NEW;b->yy_input_file N;
	yyensure_buffer_stack(SCAN);YYC=b;    // ^CLL init's a few to 0... but ^^ the last two do well to be macros
  #endif
} while (YYC->yy_buf_size=blksAt[YBT][NUMBLK]-1, ++YYG yy_buffer_stack_top<topBlkLns);
else return (F tx)&puts("Text Format Music: no squarelines found in input. Start by typing:\n[]rh \\--na\\");

#ifndef LASTMEAS
#define LASTMEAS NUMMEA
#endif

do_before();

0[(ALL(nums)vN)]=
0[(ALL(dens)vN)]=4;
0[(ALL(vC)1)]=LY ? 1 : 64;
0[(ALL(vM)1)]=
0[(ALL(vX)1)]=1;
(CLL(of)1); (CLL(oF)1);

for (uint32_t (*ptr)[3]N,*pt2 N;Do<=1+TO||(F ptr)|(F pt2)|(F tx)|(F repeatTo)|(F repeatFr)|(F of)|(F oF)|(F nums)|(F dens);Do+=1+TO) {

rwbuf(); uint64_t thisBlock=1, startWithin, timesPos=0, measTime=0; _Bool isFirst=1; static trr **ytr2 N; I=0;

for (uint32_t thisMeas=0,*ytr_n N;Do>=TO?(Do>TO?thisMeas++==LASTMEAS:thisMeas++==NUMMEA)?(F ytr_n)|(F ytr2):1:0;) {
	uint32_t last = thisBlock;
	if (!TO&&repeatTo NN&&!LY) {
		for (uint32_t i=1; i<=repeatTo[0]; ++i) if (thisMeas==repeatTo[i]) push(topYtrLns,&ytr_n),
			(ALL(ytr2)repeatTo[0]), ytr2[i-1]N, (ALL(ytr2[i-1])topYtrLns),
			memcpy(ytr2[i-1],ytr,sizeof(struct transfer) * topYtrLns);
		for (uint32_t i=1; i<=repeatTo[0]; ++i) if (repeatFr[i]&&thisMeas==repeatFr[i])
			(ALL(ytr) ytr_n[i]), rwbuf(), thisMeas=repeatTo[i], repeatFr[i]=0,
			memcpy(ytr,ytr2[i-1],sizeof(struct transfer) * ytr_n[i]), free(ytr2[i-1]), I=0;
		else if (Do&&repeatFr[i]>LASTMEAS) repeatFr[i]=(F ytr2[i-1]);
	}
	thisBlock=advanceMeas(thisBlock, thisMeas, isFirst, &ptr, &pt2, argsv); isFirst=isFirst?FREE(argsv):0;
	if (VERBOSE&&last-thisBlock&&Do>TO)
		printf("BLOCK ENDED %ld .............................................................................\n", (long)tM);
		measTime=tM;
		if (TOMEAS&&Do>TO&&thisMeas==TOMEAS) do_tms(measTime+!measTime, altTempo), do_tms(0,10), altTempo=0;
	timesPos = mBlkOff[thisMeas] + mFro[thisMeas] + blksAt[0][thisBlock-1];
	/*YYG yy_start = Do>TO?1+2*MEASURES:1+2*FIRSTMEAS;
	for (startWithin=-1;++startWithin<mFro[thisMeas];) {
		YYG yy_buffer_stack_top = topBlkLns-1;	// yylex returns 0 after last line
		while(yylex(thisMeas,startWithin,measTime,SCANNER1));
		measTime=measTime;
		#endif
	}*/
	YYG yy_start = Do>TO?1+2*SQUARES:1+2*FIRSTRUN;
	for (startWithin=-1;++startWithin<mMid[thisMeas];) {
		YYG yy_buffer_stack_top = topBlkLns-1;
		while(yylex(thisMeas,startWithin,measTime,SCANNER1));
		if (Do>TO) tM+=tiMes[timesPos];
	}
	YYG yy_start = Do>TO?1+2*MEASURES:1+2*FIRSTMEAS;
	for (startWithin=-1;++startWithin<mBak[thisMeas];) {
		YYG yy_buffer_stack_top = topBlkLns-1;
		while(yylex(thisMeas,startWithin,measTime,SCANNER1));
	}
	if (!ANLZ) printf("\\MEAS %d...\n",thisMeas);
}
	//NOW we generate the times for the secondrun. This is the ONLY reason the "single-run" has a false firstrun at all.
for (int64_t q=NUMMEA,tot=0;Do==0&&q?vL=vL/gcd(vL,mMid[q])*mMid[q]:0;--q) //generate vL
for (uint16_t i=1,j,k,X=1;q==1&&NUMBLK>=i?tL+=bSpc[i]+1:0;++i) // 1 extra b/c typelines 1 nullbyte apart in buffers
  for (j=0;k=0,i-1?bMea[i]-bMea[i-1]>=j:bMea[i]>=j;j++?tL+=mBak[X++]:0)
    if (!j) for (j=vN;j&&j--;of[j]=X+of[j]?of[j]:tot) ; else // of[] temporary: memory reused
    for (tL+=mFro[X];++k<=mMid[X];) tot+=tL[(ALL(tiMes) tL+8)]=rhsAt[i-1]NN?vL/mMid[X]:0, ++tL;


	// generate coefficients for triplets or any n-tuplets, for secondrun
	// also generate of offsets for MIDI timesig changes (oF offsets made later: memory reused)
if (Do==0?(ALL(vC)vN),(ALL(vX)vN),(ALL(vM)vN):0)
for (uint32_t *fctr N,I=0;(F fctr)||I==vN?0:1;++I) {
	if (!I) while (I>=vN?I=0:1) oF[I]=of[I],++I;
	uint64_t h=0, i; while(nums[I]>>h&&1L<<h!=nums[I]) ++h;
	vM[I]=*vC<<h; vM[I]*=nums[I]; vC[I]=*vC<<h; uint64_t V=vC[I]*=dens[I];
	for (i=I+1;I<vN&&i<vN;++i) oF[i]-=oF[I]; of[I]=oF[I];
	if (I) of[I]*=nums[I-1],of[I]/=dens[I-1],of[I]+=of[I-1]-oF[I];
	for (i=0; V>1&&~V&1&&++i; vX[I]=V/=2); // remove powers of two
	for (uint32_t h=2; V>1; V%h==0? V/=h*push(h,&fctr) :++h) ; // enumerate remaining powers
	I[(ALL(P0)vN)]N,    I[(ALL(T1)vN)]N,  I[(ALL(B1)vN)]N,  I[(ALL(NM)vN)]N,I[(ALL(PW)vN)]N;
	  (CLL(P0[I])++vC[I]),(ALL(T1[I])vC[I]),(ALL(B1[I])vC[I]),(ALL(NM[I])vC[I]--);
	for (V=vC[I];V+1;--V) if (B1[I][V]=T1[I][V]=NM[I][V]=1,fctr EN)	continue;
	else	for (uint64_t i=*fctr,j=V,k;i;--i)
		for (k=j%fctr[i]?P0[I][V]=1,fctr[i]/2:(j/=fctr[i],T1[I][V]*=fctr[i],B1[I][V]*=2,0);k>1;k/=2) ;
	while (i--) push(2,&fctr);
	for (V=vC[I];V+1?NM[I][V]=vC[I]:0;--V) for (uint32_t hh=fctr NN?*fctr:0,i=V;hh;--hh) i%fctr[hh]==0?NM[I][V]/=fctr[hh],i/=fctr[hh]:0;
	V=1; fctr NN?V<<=*fctr:0; (CLL(PW[I]) ++V);
	for (i=1; V; --V) if (fctr NN&&V<<i>>1==1LU<<*fctr) PW[I][V-1]=i++; else PW[I][V-1]=i-1;
}
}

free(tiMes);free(mBlkOff);free(mFro);free(mMid);free(mBak);free(mBlk);free(ytr);
free(bMea);free(bSpc);free(velocs);free(aboveCs);free(isFlt);free(begins);

while (NUMBLK--) free(rhTyp[NUMBLK]), free(rhsAt[NUMBLK]);	free(rhsAt);free(rhTyp);
								free(typLns);//typLns[0]=NUMLNS

for (YBT=topBlkLns;YBT--?(F blksAt[YBT])|(F blksDo[YBT])|(F YYC->yy_ch_buf)|~(F YYC):(F blksAt)|(F blksDo);) ;
free(YBS); free(SCANNER1);

if (title NN)	do_title(title), free(title);
if (copyr NN)	do_copyr(copyr), free(copyr);

do_after (tM* *vM/vL);

for (I=vN;I--?(F P0[I])|(F PW[I])|(F NM[I])|(F B1[I])|~(F T1[I]):(F P0)|(F PW)|(F NM)|(F T1)|(F B1);) ;
free(vC); free(vX); free(vM);
free(daT2);

return 0;
}
