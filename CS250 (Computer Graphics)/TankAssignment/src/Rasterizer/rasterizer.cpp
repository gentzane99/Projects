#include "Rasterizer/rasterizer.h"

int Ceiling(float f)
{
    int i = static_cast<int>(f);

    if (static_cast<float>(i) == f)
        return i;

    return i + 1;
}

void DrawMidpointLine(const Point2D & p1, const Point2D & p2, sf::Image & image)
{
    int x = (int)round(p1.x);
    int y = (int)round(p1.y);

    int dx    = (int)round(p2.x) - x;
    int dy    = (int)round(p2.y) - y;
    int xStep = 1, yStep = 1;

    if (dx < 0)
    {
        xStep = -1;
        dx    = -dx;
    }
    if (dy < 0)
    {
        yStep = -1;
        dy    = -dy;
    }

	//Checks if the position of x and y is on the screen
	if ((unsigned)x < image.getSize().x && x > 0 && (unsigned)y < image.getSize().y && y > 0)
		image.setPixel(x, y, sf::Color((sf::Uint8)p1.r, (sf::Uint8)p1.g, (sf::Uint8)p1.b));

    if (abs(dy) > abs(dx)) // |m|>1
    {
        int dstart, dn, dne;
        dstart = 2 * dx - dy;
        dn     = dx;
        dne    = dx - dy;

        while (dy--)
        {
            y += yStep;

            if (dstart > 0)
            {
                dstart += dne;
                x += xStep;
            }
            else
                dstart += dn;

			if ((unsigned)x < image.getSize().x && x > 0 && (unsigned)y < image.getSize().y && y > 0)
				image.setPixel(x, y, sf::Color((sf::Uint8)p1.r, (sf::Uint8)p1.g, (sf::Uint8)p1.b));
        }
    }
    else // |m|<1
    {
        int dstart, de, dne;
        dstart = 2 * dy - dx;
        de     = dy;
        dne    = dy - dx;

        while (dx--)
        {
            x += xStep;

            if (dstart > 0)
            {
                dstart += dne;
                y += yStep;
            }
            else
                dstart += de;

			//Checks if the position of x and y is on the screen
			if ((unsigned)x < image.getSize().x && x > 0 && (unsigned)y < image.getSize().y && y > 0)
				image.setPixel(x, y, sf::Color((sf::Uint8)p1.r, (sf::Uint8)p1.g, (sf::Uint8)p1.b));
        }
    }
}

void DrawTriangleSolid(const Point2D & p0, const Point2D & p1, const Point2D & p2, sf::Image & image)
{
    // Select TOP, MIDDLE and BOTTOM vertices
    // --------------------------------------
    const Point2D *top, *middle, *bottom;
    bool           middle_is_left = false;

    if (p0.val[1] < p1.val[1]) // case 4, 5, or 6
    {
        if (p2.val[1] < p0.val[1]) // case 4
        {
            top            = &p2;
            middle         = &p0;
            bottom         = &p1;
            middle_is_left = true;
        }
        else
        {
            top = &p0;
            if (p1.val[1] < p2.val[1]) // case 5
            {
                middle         = &p1;
                bottom         = &p2;
                middle_is_left = true;
            }
            else // case 6
            {
                middle         = &p2;
                bottom         = &p1;
                middle_is_left = false;
            }
        }
    }
    else // case 1, 2 or 3
    {
        if (p2.val[1] < p1.val[1]) // case 2
        {
            top    = &p2;
            middle = &p1;

            bottom         = &p0;
            middle_is_left = false;
        }
        else
        {
            top = &p1;
            if (p0.val[1] < p2.val[1]) // case 3
            {
                middle         = &p0;
                bottom         = &p2;
                middle_is_left = false;
            }
            else // case 1
            {
                middle         = &p2;
                bottom         = &p0;
                middle_is_left = true;
            }
        }
    }

    // TOP to MIDDLE
    // -------------
    // Select LEFT and RIGHT edge endpoints to use from the top to the middle
    // ----------------------------------------------------------------------
    const Point2D *left, *right;
    if (middle_is_left)
    {
        left  = middle;
        right = bottom;
    }
    else
    {
        right = middle;
        left  = bottom;
    }

    // Calculate the x increments along the LEFT and RIGHT edges (the inverse of the slope
    float xIncLeft  = (left->val[0] - top->val[0]) / (left->val[1] - top->val[1]);
    float xIncRight = (right->val[0] - top->val[0]) / (right->val[1] - top->val[1]);

    // Initial values
    int   y    = Ceiling(top->val[1]);
    int   yMax = Ceiling(middle->val[1]) - 1;
    float xL   = top->val[0]; // xL MUST ALWAYS be a double, the ceiling is applied to x and xMax
    float xR   = top->val[0]; // xL MUST ALWAYS be a double, the ceiling is applied to x and xMax
    int   x;
    int   xMax = Ceiling(xR) - 1;

    // Initial Color Interpolation (Plane Equation Parameters)
    // RED
    float v1R[3] = {middle->val[0] - top->val[0], middle->val[1] - top->val[1], static_cast<float>(middle->col[0] - top->col[0])};
    float v2R[3] = {bottom->val[0] - top->val[0], bottom->val[1] - top->val[1], static_cast<float>(bottom->col[0] - top->col[0])};
    // GREEN
    float v1G[3] = {middle->val[0] - top->val[0], middle->val[1] - top->val[1], static_cast<float>(middle->col[1] - top->col[1])};
    float v2G[3] = {bottom->val[0] - top->val[0], bottom->val[1] - top->val[1], static_cast<float>(bottom->col[1] - top->col[1])};
    // BLUE
    float v1B[3] = {middle->val[0] - top->val[0], middle->val[1] - top->val[1], static_cast<float>(middle->col[2] - top->col[2])};
    float v2B[3] = {bottom->val[0] - top->val[0], bottom->val[1] - top->val[1], static_cast<float>(bottom->col[2] - top->col[2])};
    // NORMALS
    float nR[3] = {v1R[1] * v2R[2] - v1R[2] * v2R[1], v1R[2] * v2R[0] - v1R[0] * v2R[2], v1R[0] * v2R[1] - v1R[1] * v2R[0]};
    float nG[3] = {v1G[1] * v2G[2] - v1G[2] * v2G[1], v1G[2] * v2G[0] - v1G[0] * v2G[2], v1G[0] * v2G[1] - v1G[1] * v2G[0]};
    float nB[3] = {v1B[1] * v2B[2] - v1B[2] * v2B[1], v1B[2] * v2B[0] - v1B[0] * v2B[2], v1B[0] * v2B[1] - v1B[1] * v2B[0]};
    // Increments
    float rIncX = -nR[0] / nR[2];
    float rIncY = -nR[1] / nR[2];
    float gIncX = -nG[0] / nG[2];
    float gIncY = -nG[1] / nG[2];
    float bIncX = -nB[0] / nB[2];
    float bIncY = -nB[1] / nB[2];

    float rL = top->col[0];
    float gL = top->col[1];
    float bL = top->col[2];

    float r, g, b;

    // Start the loop, from the y_top to y_middle
    while (y <= yMax)
    {
        // Loop along the scanline, from left to right
        x    = Ceiling(xL);
        xMax = Ceiling(xR) - 1;

        r = rL;
        g = gL;
        b = bL;

        while (x <= xMax)
        {
			//Checks if the position of x and y is on the screen
			if ((unsigned)x < image.getSize().x && x > 0 && (unsigned)y < image.getSize().y && y > 0)
				image.setPixel(x, y, sf::Color((sf::Uint8)r, (sf::Uint8)g, (sf::Uint8)b));

            ++x;

            r += rIncX;
            g += gIncX;
            b += bIncX;
        }

        xL += xIncLeft;
        xR += xIncRight;
        ++y;

        rL += rIncY + rIncX * xIncLeft;
        gL += gIncY + gIncX * xIncLeft;
        bL += bIncY + bIncX * xIncLeft;
    }

    // MIDDLE to BOTTOM
    // ----------------
    // Select LEFT and RIGHT edge endpoints to use from the top to the middle
    // ----------------------------------------------------------------------
    // Initial values
    y    = Ceiling(middle->val[1]);
    yMax = Ceiling(bottom->val[1]) - 1;

    if (middle_is_left)
    {
        xIncLeft = (bottom->val[0] - left->val[0]) / (bottom->val[1] - left->val[1]);
        xL       = left->val[0];

        rL = middle->col[0];
        gL = middle->col[1];
        bL = middle->col[2];
    }
    else
    {
        xIncRight = (bottom->val[0] - right->val[0]) / (bottom->val[1] - right->val[1]);
        xR        = right->val[0];
    }

    // Start the loop, from the y_top to y_middle
    while (y <= yMax)
    {
        x    = Ceiling(xL);
        xMax = Ceiling(xR) - 1;

        r = rL;
        g = gL;
        b = bL;

        // Loop along the scanline, from left to right
        while (x <= xMax)
        {
			//Checks if the position of x and y is on the screen
			if ((unsigned)x < image.getSize().x && x > 0 && (unsigned)y < image.getSize().y && y > 0)
				image.setPixel(x, y, sf::Color((sf::Uint8)r, (sf::Uint8)g, (sf::Uint8)b));

            ++x;

            r += rIncX;
            g += gIncX;
            b += bIncX;
        }

        xL += xIncLeft;
        xR += xIncRight;
        ++y;

        rL += rIncY + rIncX * xIncLeft;
        gL += gIncY + gIncX * xIncLeft;
        bL += bIncY + bIncX * xIncLeft;
    }
}
