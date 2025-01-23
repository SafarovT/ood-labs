import {ICanvas} from './classes/interfaces/ICanvas'
import {Rectangle} from './classes/Rectangle'
import {Ellipse} from './classes/Ellipse'
import {ShapesGroup} from './classes/ShapesGroup'
import {Triangle} from './classes/Triangle'
import {Slide} from './classes/Slide'
import {LineStyle, FillStyle} from './types/styles'

const BLACK = {
    r: 0,
    g: 0,
    b: 0,
    a: 255,
}

const BLUE = {
    r: 0,
    g: 0,
    b: 255,
    a: 255,
}

const DARK_BLUE = {
    r: 0,
    g: 0,
    b: 139,
    a: 255,
}

const LIGHT_GRAY = {
    r: 211,
    g: 211,
    b: 211,
    a: 255,
}

const YELLOW = {
    r: 255,
    g: 255,
    b: 0,
    a: 255,
}

const LIGHT_BLUE = {
    r: 173,
    g: 216,
    b: 230,
    a: 255,
}

const BROWN = {
    r: 165,
    g: 42,
    b: 42,
    a: 255,
}

const DARK_RED = {
    r: 139,
    g: 0,
    b: 0,
    a: 255,
}

const DARK_BROWN = {
    r: 101,
    g: 67,
    b: 33,
    a: 255,
}

const LIGHT_YELLOW = {
    r: 255,
    g: 255,
    b: 224,
    a: 255,
}

const MINT_GREEN = {
    r: 152,
    g: 255,
    b: 152,
    a: 255,
}

const RED = {
    r: 255,
    g: 0,
    b: 0,
    a: 255,
}

function demoShapes(canvas: ICanvas): void {
    const lineStyle: LineStyle = { color: BLACK, thickness: 2 }

    const carBody = new Rectangle({ coordinates: { x: 100, y: 150 }, width: 200, height: 60 }, lineStyle, { color: BLUE })
    const carRoof = new Rectangle({coordinates: {x: 140, y: 100}, width: 100, height: 50}, lineStyle, {color: DARK_BLUE})

    const roofFrame1 = { coordinates: { x: 110, y: 100 }, width: 100, height: 50 }
    const roofTriangle1 = new Triangle(
        roofFrame1,
        lineStyle,
        { color: DARK_BLUE }
    )

    const roofFrame2 = { coordinates: { x: 180, y: 100 }, width: 100, height: 50 }
    const roofTriangle2 = new Triangle(
        roofFrame2,
        lineStyle,
        { color: DARK_BLUE }
    )

    const wheel1 = new Ellipse({ coordinates: { x: 100, y: 170 }, width: 40, height: 80 }, lineStyle, { color: BLACK })
    const wheel2 = new Ellipse({ coordinates: { x: 240, y: 170 }, width: 40, height: 80 }, lineStyle, { color: BLACK })

    const window1 = new Rectangle({ coordinates: { x: 140, y: 110 }, width: 40, height: 30 }, lineStyle, { color: LIGHT_GRAY })
    const window2 = new Rectangle({ coordinates: { x: 200, y: 110 }, width: 40, height: 30 }, lineStyle, { color: LIGHT_GRAY })

    const headlight1 = new Ellipse({ coordinates: { x: 120, y: 170 }, width: 20, height: 10 }, lineStyle, { color: YELLOW })
    const headlight2 = new Ellipse({ coordinates: { x: 250, y: 170 }, width: 20, height: 10 }, lineStyle, { color: YELLOW })

    const carGroup = new ShapesGroup([
        carBody,
        carRoof,
        roofTriangle1,
        roofTriangle2,
        wheel1,
        wheel2,
        window1,
        window2,
        headlight1,
        headlight2,
    ])
    carGroup.setFrame({ coordinates: { x: 0, y: 0 }, width: 400, height: 250 })

    const sun = new Ellipse({ coordinates: { x: 500, y: -150  }, width: 100, height: 100 }, lineStyle, { color: YELLOW })

    const slide = new Slide()
    slide.addElement('car', carGroup)
    slide.addElement('sun', sun)

    slide.draw(canvas)
}

export {
    demoShapes,
}