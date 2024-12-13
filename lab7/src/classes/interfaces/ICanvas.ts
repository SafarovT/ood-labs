import type {Point} from '../../types/point'
import type {RGBA} from '../../types/colors'

abstract class ICanvas {
    abstract drawLine(start: Point, end: Point): void
    abstract drawEllipse(center: Point, width: number, height: number): void
    abstract fillEllipse(center: Point, width: number, height: number): void
    abstract fillPolygon(points: Point[]): void
    abstract setFillColor(color: RGBA): void
    abstract setLineColor(color: RGBA): void
    abstract setLineThickness(thickness: number): void
}

export {
    ICanvas,
}