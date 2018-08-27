#ifndef POINT_H
#define POINT_H

// Internal
#include "base_dto.h"

namespace dto
{
    class Point: public BaseDto
    {
        Q_GADGET

        Q_PROPERTY(double x READ x WRITE setX)
        Q_PROPERTY(double y READ y WRITE setY)
        Q_PROPERTY(double Z READ z WRITE setZ)
        Q_PROPERTY(Frame frame READ frame WRITE setFrame)

    public:
        enum Frame
        {
            Wgs84,
            Pz90_11
        };

        double x() const;
        void setX(double x);

        double y() const;
        void setY(double y);

        double z() const;
        void setZ(double Z);

        Frame frame() const;
        void setFrame(Frame frame);

    private:
        double m_x;
        double m_y;
        double m_Z;
        Frame m_frame;
    };
}

#endif // POINT_H
