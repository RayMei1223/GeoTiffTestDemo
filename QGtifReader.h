#ifndef QGTIFREADER_H
#define QGTIFREADER_H

#include "geotiff.h"
#include "xtiffio.h"
#include "geo_normalize.h"

#include <QObject>
#include <QImage>
#include <QGeoCoordinate>
#include <QPoint>

#include "global.h"

class QGtifReader: public QObject
{
    Q_OBJECT
signals:
    void fileChanged();

public:
    Q_DECLARE_STATIC_INSTANCE(QGtifReader);

    auto setFilePath(const QString &filepath) -> bool;
    auto isVaild() const -> bool { return _tif && _gtif; }

public:
    auto point2GeoCoordinate(const QPoint &pos) const -> QGeoCoordinate;
    auto geoCoordinate2Point(const QGeoCoordinate &coord) const -> QPoint;

    auto getDistanceM(const QGeoCoordinate &lh, const QGeoCoordinate &rh) const -> double;

    /*!
     * \param point x at image map
     * \param point y at image map
     */
    auto getDistanceMByPoint(const QPointF &x, const QPointF &y) const -> double;
    auto getMap() const -> const QImage & { return _map; }
    auto getPCSInfo() const -> QString;

private:
    QGtifReader(QObject *parent = nullptr);
    ~QGtifReader();

private:
    QImage _map;

    TIFF     *_tif;  /* TIFF-level descriptor */
    GTIF     *_gtif; /* GeoKey-level descriptor */
    GTIFDefn *_defn;
};

#define qGtifReader (QGtifReader::Instance())

#endif // QGTIFREADER_H
