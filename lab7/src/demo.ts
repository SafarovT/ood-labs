import {ICanvas} from './classes/interfaces/ICanvas'
import {Rectangle} from './classes/Rectangle'
import {Ellipse} from './classes/Ellipse'
import {ShapesGroup} from './classes/ShapesGroup'
import {Slide} from './classes/Slide'
import {LineStyle, FillStyle} from './types/styles'

const BLACK = {
    r: 0,
    g: 0,
    b: 0,
    a: 255,
}

const LIGHT_BLUE = {
    r: 144,
    g: 213,
    b: 255,
    a: 255,
}

const MINT_GREEN = {
    r: 173,
    g: 235,
    b: 179,
    a: 255,
}

const RED = {
    r: 255,
    g: 0,
    b: 0,
    a: 255,
}

const YELLOW = {
    r: 0,
    g: 255,
    b: 255,
    a: 255,
}

function demoShapes(canvas: ICanvas): void {
    const lineStyle: LineStyle = { color: BLACK, thickness: 2 };
    const fillStyle: FillStyle = { color: LIGHT_BLUE };

    const rectangle = new Rectangle({ coordinates: { x: 10, y: 20 }, width: 100, height: 50 }, lineStyle, fillStyle);
    const ellipse = new Ellipse({ coordinates: { x: 50, y: 100 }, width: 80, height: 40 }, lineStyle, fillStyle);

    rectangle.setFillStyle({ color: MINT_GREEN });
    ellipse.setLineStyle({ color: RED, thickness: 3 });

    const group = new ShapesGroup([rectangle, ellipse]);

    group.setFrame({ coordinates: { x: 0, y: 0 }, width: 300, height: 200 });

    const smallRectangle = new Rectangle({ coordinates: { x: 20, y: 30 }, width: 40, height: 20 }, lineStyle, fillStyle);
    group.addShape(smallRectangle);

    const slide = new Slide();
    slide.addElement("group1", group);

    const soloEllipse = new Ellipse({ coordinates: { x: 200, y: 150 }, width: 60, height: 30 }, lineStyle, { color: YELLOW });
    slide.addElement("ellipse1", soloEllipse);

    slide.draw(canvas);
}

export {
    demoShapes,
}