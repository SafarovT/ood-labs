import type {RGBA} from './colors'

type LineStyle = {
    color: RGBA | null
    thickness: number | null
}

type FillStyle =  {
    color: RGBA | null
}

export type {
    LineStyle,
    FillStyle,
}