#ifndef dplyr_white_list_H
#define dplyr_white_list_H

namespace dplyr{
    
inline bool is_bare_vector( SEXP x){
    SEXP att = ATTRIB(x) ;
    
    // fine if there is no attributes
    if( att == R_NilValue ) return true ;
    
    // only allow R_Names. as in R's do_isvector
    while( att != R_NilValue ){
        if( TAG(att) != R_NamesSymbol ) return false ;
        att = CDR(att) ;    
    }
    
    return true ;
}

inline bool white_list(SEXP x){
    switch( TYPEOF(x) ){
    case INTSXP:   return Rf_inherits(x, "Date") || Rf_inherits(x, "POSIXct" ) || Rf_inherits(x, "factor" ) || is_bare_vector( x ) ;
    case REALSXP:  return Rf_inherits(x, "Date") || Rf_inherits(x, "POSIXct" ) || is_bare_vector( x ) ;
    case LGLSXP:   return is_bare_vector( x ) ;
    case STRSXP:   return is_bare_vector( x ) ;
    case CPLXSXP:  return is_bare_vector( x ) ;
    case RAWSXP:   return is_bare_vector( x ) ;
    
    case VECSXP:   return is_bare_vector( x ) ;
    
    default: break ;
    }
    return false ;
}

}
#endif

