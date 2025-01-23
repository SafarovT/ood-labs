type RGBA = {
    r: number,
    g: number,
    b: number,
    a: number,
}

function rgbaToString(rgba: RGBA): string {
    return `rgba(${rgba.r}, ${rgba.g}, ${rgba.b}, ${rgba.a})`
}

export type {
    RGBA,
}

export {
    rgbaToString,
}