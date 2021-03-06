/*===========================================================================
 *
 *                            PUBLIC DOMAIN NOTICE
 *               National Center for Biotechnology Information
 *
 *  This software/database is a "United States Government Work" under the
 *  terms of the United States Copyright Act.  It was written as part of
 *  the author's official duties as a United States Government employee and
 *  thus cannot be copyrighted.  This software/database is freely available
 *  to the public for use. The National Library of Medicine and the U.S.
 *  Government have not placed any restriction on its use or reproduction.
 *
 *  Although all reasonable efforts have been taken to ensure the accuracy
 *  and reliability of the software and data, the NLM and the U.S.
 *  Government do not and cannot warrant the performance or results that
 *  may be obtained by using this software or data. The NLM and the U.S.
 *  Government disclaim all warranties, express or implied, including
 *  warranties of performance, merchantability or fitness for any particular
 *  purpose.
 *
 *  Please cite the author in any work or product based on this material.
 *
 * ===========================================================================
 *
 */

#ifndef _h_sra_sort_csra_pair_
#define _h_sra_sort_csra_pair_

#ifndef _h_sra_sort_db_pair_
#include "db-pair.h"
#endif


#define SEQUENCE_BEFORE_SECONDARY 1


/*--------------------------------------------------------------------------
 * forwards
 */
struct TablePair;
struct ColumnWriter;


/*--------------------------------------------------------------------------
 * cSRAPair
 *  interface to pairing of source and destination tables
 */
typedef struct cSRAPair cSRAPair;
struct cSRAPair
{
    DbPair dad;

    /* for ultimate metadata */
    int64_t first_half_aligned_spot;
    int64_t first_unaligned_spot;

    /* the reference table */
    struct TablePair *reference;

    /* the alignment tables */
    struct TablePair *prim_align, *sec_align, *evidence_align;

    /* the sequence table */
    struct TablePair *sequence;

    /* mapping indices */
    struct MapFile *pa_idx, *sa_idx, *seq_idx;
};


/* Make
 *  makes an object based upon open source and destination VDatabase objects
 */
DbPair *cSRAPairMake ( const ctx_t *ctx,
    struct VDatabase const *src, struct VDatabase *dst, const char *name );


/* MakeFirstHalfAlignedRowIdCaptureWriter
 *  a simple monitor on SEQUENCE.PRIMARY_ALIGNMENT_ID looking for
 *  half-aligned spots and capturing the first occurrence.
 */
struct ColumnWriter *cSRAPairMakeFirstHalfAlignedRowIdCaptureWriter ( cSRAPair *self,
    const ctx_t *ctx, struct ColumnWriter *writer );


#endif /* _h_sra_sort_csra_pair_ */
