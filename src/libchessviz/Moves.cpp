#include "Moves.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

static int IsPawnMoveCorrect(Chessboard* chessboard, Move move, Errors* error)
{
    int dir = (move.who.side == FigureSideWhite) ? 1 : -1;
    char tn = move.to.number, tl = move.to.letter, fn = move.from.number,
         fl = move.from.letter;
    if (move.type == MoveTypeAttack) {
        if (tn - fn == dir && (tl - fl == 1 || tl - fl == -1)) {
            if (move.who.side == FigureSideWhite) {
                if (chessboard
                            ->cells[move.to.number - '1'][move.to.letter - 'a']
                            .side
                    == FigureSideBlack) {
                    return 0;
                }
            } else {
                if (chessboard
                            ->cells[move.to.number - '1'][move.to.letter - 'a']
                            .side
                    == FigureSideWhite) {
                    return 0;
                }
            }
        } else {
            error->isTrigger = 1;
            return 1;
        }
    } else if (dir == 1 ? (fn == '2') : (fn == '7')) {
        if (fl == tl && tn - fn <= 2 * dir
            && chessboard->cells[fn + (char)dir - '1'][fl - 'a'].side
                    == FigureSideNone) {
            return 0;
        } else {
            error->isTrigger = 1;
            return 1;
        }
    } else {
        if (move.from.letter == move.to.letter
            && move.to.number - move.from.number == dir) {
            return 0;
        } else {
            // error
            return 1;
        }
    }
    return 1;
}

static int IsKnightMoveCorrect(Move move, Errors* error)
{
    if (move.to.letter - move.from.letter == 2
        || move.to.letter - move.from.letter == -2) {
        if (move.to.number - move.from.number == 1
            || move.to.number - move.from.number == -1) {
            return 0;
        } else {
            error->isTrigger = 1;
            return 1;
        }

    } else if (
            move.to.number - move.from.number == 2
            || move.to.number - move.from.number == -2) {
        if (move.to.letter - move.from.letter == 1
            || move.to.letter - move.from.letter == -1) {
            return 0;
        } else {
            error->isTrigger = 1;
            return 1;
        }
    } else {
        error->isTrigger = 1;
        return 1;
    }
    return 0;
}

static int IsBishopMoveCorrect(Chessboard* chessboard, Move move, Errors* error)
{
    char tl = move.to.letter - 'a', fl = move.from.letter - 'a',
         tn = move.to.number - '1', fn = move.from.number - '1';
    if (tl - fl == tn - fn || tl - fl == -(tn - fn)) {
        if (tl - fl > 0) {
            if (tn - fn > 0) {
                for (int i = fn + 1, j = fl + 1; i != tn; i++, j++) {
                    if (chessboard->cells[i][j].side != FigureSideNone) {
                        error->isTrigger = 1;
                        return 1;
                    }
                }
                return 0;
            } else {
                for (int i = fn - 1, j = fl + 1; i != tn; i--, j++) {
                    if (chessboard->cells[i][j].side != FigureSideNone) {
                        error->isTrigger = 1;
                        return 1;
                    }
                }
                return 0;
            }
        } else if (tn - fn > 0) {
            for (int i = fn + 1, j = fl - 1; i != tn; i++, j--) {
                if (chessboard->cells[i][j].side != FigureSideNone) {
                    error->isTrigger = 1;
                    return 1;
                }
            }
            return 0;
        } else {
            for (int i = fn + 1, j = fl - 1; i != tn; i--, j--) {
                if (chessboard->cells[i][j].side != FigureSideNone) {
                    error->isTrigger = 1;
                    return 1;
                }
            }
            return 0;
        }
    } else {
        error->isTrigger = 1;
        return 1;
    }
    return 0;
}

static int IsRookMoveCorrect(Chessboard* chessboard, Move move, Errors* error)
{
    error->isTrigger = 0;
    char tl = move.to.letter - 'a', fl = move.from.letter - 'a',
         tn = move.to.number - '1', fn = move.from.number - '1';
    if (tl == fl) {
        if (tn - fn > 0) {
            for (int i = fn + 1, j = fl; i != tn; i++) {
                if (chessboard->cells[i][j].side != FigureSideNone) {
                    error->isTrigger = 1;
                    return 1;
                }
            }
            return 0;
        } else {
            for (int i = fn - 1, j = fl; i != tn; i--) {
                if (chessboard->cells[i][j].side != FigureSideNone) {
                    error->isTrigger = 1;
                    return 1;
                }
            }
            return 0;
        }
    } else if (tn == fn) {
        if (tl - fl > 0) {
            for (int i = fn, j = fl + 1; j != tl; j++) {
                if (chessboard->cells[i][j].side != FigureSideNone) {
                    error->isTrigger = 1;
                    return 1;
                }
            }
            return 0;
        } else {
            for (int i = fn, j = fl - 1; j != tl; j--) {
                if (chessboard->cells[i][j].side != FigureSideNone) {
                    error->isTrigger = 1;
                    return 1;
                }
            }
            return 0;
        }
    } else {
        error->isTrigger = 1;
        return 1;
    }
    return 0;
}

static int IsQueenMoveCorrect(Chessboard* chessboard, Move move, Errors* error)
{
    if (IsBishopMoveCorrect(chessboard, move, error) == 0
        || IsRookMoveCorrect(chessboard, move, error) == 0) {
        return 0;
    } else
        return 1;
}

static int IsKingMoveCorrect(Move move, Errors* error)
{
    char tl = move.to.letter, fl = move.from.letter, tn = move.to.number,
         fn = move.from.number;
    if (tl - fl > -2 && tl - fl < 2) {
        if (tn - fn > -2 && tn - fn < 2) {
            return 0;
        } else {
            error->isTrigger = 1;
            return 1;
        }
    } else {
        error->isTrigger = 1;
        return 1;
    }
    return 0;
}

static int MoveIsCorrect(Chessboard* chessboard, Move move, Errors* error)
{
    Figure figureFrom
            = chessboard->cells[move.from.number - '1'][move.from.letter - 'a'];
    Figure figureTo
            = chessboard->cells[move.to.number - '1'][move.to.letter - 'a'];
    if (figureFrom.type == move.who.type) {
        if (figureFrom.side == move.who.side) {
            if (move.type == MoveTypeNormal) {
                if (figureTo.side == FigureSideNone
                    && figureTo.type == FigureTypeNone) {
                }
            } else if (
                    figureTo.side != figureFrom.side
                    && figureTo.side != FigureSideNone) {
            } else {
                error->isTrigger = 1;
                return 1;
            }
        } else {
            error->isTrigger = 1;
            return 1;
        }
    } else {
        error->isTrigger = 1;
        return 1;
    }

    if (move.who.type == FigureTypePawn) {
        return IsPawnMoveCorrect(chessboard, move, error);
    } else if (move.who.type == FigureTypeKnight) {
        return IsKnightMoveCorrect(move, error);
    } else if (move.who.type == FigureTypeBishop) {
        return IsBishopMoveCorrect(chessboard, move, error);
    } else if (move.who.type == FigureTypeRook) {
        return IsRookMoveCorrect(chessboard, move, error);
    } else if (move.who.type == FigureTypeQueen) {
        return IsQueenMoveCorrect(chessboard, move, error);
    } else if (move.who.type == FigureTypeKing) {
        return IsKingMoveCorrect(move, error);
    } else {
        return 1;
    }
}

static int IsExtraMoveCorrect(Chessboard* chessboard, Move move, Errors* error)
{
    if (error->isTrigger == 1) {
        return 1;
    }
    if (move.extra == ExtraTypeShortCastling) {
        if (move.who.side == FigureSideWhite
            && chessboard->cells[0][7].type == FigureTypeRook
            && chessboard->cells[0][6].type == FigureTypeNone
            && chessboard->cells[0][5].type == FigureTypeNone
            && chessboard->cells[0][4].type == FigureTypeKing) {
            chessboard->cells[0][4]
                    = (Figure){.side = FigureSideNone, .type = FigureTypeNone};
            chessboard->cells[0][7]
                    = (Figure){.side = FigureSideNone, .type = FigureTypeNone};
            chessboard->cells[0][6]
                    = (Figure){.side = FigureSideWhite, .type = FigureTypeKing};
            chessboard->cells[0][5]
                    = (Figure){.side = FigureSideWhite, .type = FigureTypeRook};
            return 0;
        } else if (
                move.who.side == FigureSideBlack
                && chessboard->cells[7][7].type == FigureTypeRook
                && chessboard->cells[7][6].type == FigureTypeNone
                && chessboard->cells[7][5].type == FigureTypeNone
                && chessboard->cells[7][4].type == FigureTypeKing) {
            chessboard->cells[7][4]
                    = (Figure){.side = FigureSideNone, .type = FigureTypeNone};
            chessboard->cells[7][7]
                    = (Figure){.side = FigureSideNone, .type = FigureTypeNone};
            chessboard->cells[7][6]
                    = (Figure){.side = FigureSideWhite, .type = FigureTypeKing};
            chessboard->cells[7][5]
                    = (Figure){.side = FigureSideWhite, .type = FigureTypeRook};
            return 0;
        } else {
            error->isTrigger = 1;
            return 1;
        }
    } else if (move.extra == ExtraTypeLongCastling) {
        if (move.who.side == FigureSideWhite
            && chessboard->cells[0][0].type == FigureTypeRook
            && chessboard->cells[0][1].type == FigureTypeNone
            && chessboard->cells[0][2].type == FigureTypeNone
            && chessboard->cells[0][3].type == FigureTypeNone
            && chessboard->cells[0][4].type == FigureTypeKing) {
            chessboard->cells[0][4]
                    = (Figure){.side = FigureSideNone, .type = FigureTypeNone};
            chessboard->cells[0][0]
                    = (Figure){.side = FigureSideNone, .type = FigureTypeNone};
            chessboard->cells[0][2]
                    = (Figure){.side = FigureSideWhite, .type = FigureTypeKing};
            chessboard->cells[0][3]
                    = (Figure){.side = FigureSideWhite, .type = FigureTypeRook};
            return 0;
        } else if (
                move.who.side == FigureSideBlack
                && chessboard->cells[7][0].type == FigureTypeRook
                && chessboard->cells[7][1].type == FigureTypeNone
                && chessboard->cells[7][2].type == FigureTypeNone
                && chessboard->cells[7][3].type == FigureTypeNone
                && chessboard->cells[7][4].type == FigureTypeKing) {
            chessboard->cells[7][4]
                    = (Figure){.side = FigureSideNone, .type = FigureTypeNone};
            chessboard->cells[7][0]
                    = (Figure){.side = FigureSideNone, .type = FigureTypeNone};
            chessboard->cells[7][2]
                    = (Figure){.side = FigureSideWhite, .type = FigureTypeKing};
            chessboard->cells[7][3]
                    = (Figure){.side = FigureSideWhite, .type = FigureTypeRook};
            return 0;
        } else {
            error->isTrigger = 1;
            return 1;
        }
    } else {
        if (move.from.letter - 'a' > 7 || move.from.number - '1' > 7
            || move.to.letter - 'a' > 7 || move.to.number - '1' > 7) {
            error->isTrigger = 1;
            return 1;
        }
        if (move.who.type == FigureTypePawn) {
            if (move.who.side == FigureSideWhite && move.to.number == '8'
                && chessboard->cells[move.to.number - '1'][move.to.letter - 'a']
                                .type
                        == FigureTypeNone) {
                if (move.extra == ExtraTypeTransToQueen) {
                    chessboard
                            ->cells[move.to.number - '1'][move.to.letter - 'a']
                            = (Figure){
                                    .side = FigureSideWhite,
                                    .type = FigureTypeQueen};
                } else if (move.extra == ExtraTypeTransToRook) {
                    chessboard
                            ->cells[move.to.number - '1'][move.to.letter - 'a']
                            = (Figure){
                                    .side = FigureSideWhite,
                                    .type = FigureTypeRook};
                } else if (move.extra == ExtraTypeTransToKnight) {
                    chessboard
                            ->cells[move.to.number - '1'][move.to.letter - 'a']
                            = (Figure){
                                    .side = FigureSideWhite,
                                    .type = FigureTypeKnight};
                } else {
                    chessboard
                            ->cells[move.to.number - '1'][move.to.letter - 'a']
                            = (Figure){
                                    .side = FigureSideWhite,
                                    .type = FigureTypeBishop};
                }
            } else if (
                    move.who.side == FigureSideBlack && move.to.number == '1'
                    && chessboard->cells[move.to.number - '1']
                                        [move.to.letter - 'a']
                                                .type
                            == FigureTypeNone) {
                if (move.extra == ExtraTypeTransToQueen) {
                    chessboard
                            ->cells[move.to.number - '1'][move.to.letter - 'a']
                            = (Figure){
                                    .side = FigureSideBlack,
                                    .type = FigureTypeQueen};
                } else if (move.extra == ExtraTypeTransToRook) {
                    chessboard
                            ->cells[move.to.number - '1'][move.to.letter - 'a']
                            = (Figure){
                                    .side = FigureSideBlack,
                                    .type = FigureTypeRook};
                } else if (move.extra == ExtraTypeTransToKnight) {
                    chessboard
                            ->cells[move.to.number - '1'][move.to.letter - 'a']
                            = (Figure){
                                    .side = FigureSideBlack,
                                    .type = FigureTypeKnight};
                } else {
                    chessboard
                            ->cells[move.to.number - '1'][move.to.letter - 'a']
                            = (Figure){
                                    .side = FigureSideBlack,
                                    .type = FigureTypeBishop};
                }
            }
        } else {
            error->isTrigger = 1;
            return 1;
        }
    }
    error->isTrigger = 1;
    return 1;
}

int DoMove(Chessboard* chessboard, Move move, Errors* error)
{
    error->index = 1;
    if (move.extra == ExtraTypeNone || move.extra == ExtraTypeCheckmate
        || move.extra == ExtraTypeCheck || move.extra == ExtraTypeEnPassant) {
        if (MoveIsCorrect(chessboard, move, error) != 0) {
            return 1;
        }
    } else if (IsExtraMoveCorrect(chessboard, move, error) == 0) {
        return 0;
    } else {
        return 1;
    }
    chessboard->cells[move.to.number - '1'][move.to.letter - 'a']
            = chessboard->cells[move.from.number - '1'][move.from.letter - 'a'];
    chessboard->cells[move.from.number - '1'][move.from.letter - 'a']
            = (Figure){.side = FigureSideNone, .type = FigureTypeNone};

    return 0;
}