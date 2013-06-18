/*
 *
 *    NoteView.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/17
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef NOTEVIEW_H
#define NOTEVIEW_H

#include <QLabel>
#include "AbstractGridView.h"

#include "PianoPainter.h"

/**
 *  @brief シーケンスからピアノロールを表示するクラス．
 */
class NoteView : public AbstractGridView
{
public:
    explicit NoteView(
            int divCount,
            int noteHeight,
            int beatWidth,
            const vsq::Sequence *sequence,
            int trackId,
            QWidget *parent = 0
            );

    virtual ~NoteView();
    void setNoteHeight(int noteHeight);

    QColor barLineColor;        //! @brief 小節線の描画色
    QColor assistLineColor;     //! @brief 補助線の描画色

    QColor noteColor;           //! @brief 音符の描画色
    QColor noteTextColor;       //! @brief 音符のテキスト描画色
    QColor noteInvalidColor;    //! @brief 音符の情報が不適切な際の描画色
    QColor noteSelectedColor;   //! @brief 音符の選択時の描画色

    /**
     *  @brief ノート番号に対応する y 座標を返します．ビュー上での位置はピアノロール上で上辺に対応します．
     */
    int yAt(int note);

    int noteHeight() const
    {
        return _noteHeight;
    }
public slots:
    // @Override
    virtual void beatWidthChanged(int w);
    // @Override
    virtual void noteHeightChanged(int h);

protected:
    // @Override
    virtual void paintBefore(const QRect &rect, QPainter *painter);
    // @Override
    virtual void drawBarLine(vsq::tick_t tick, QPainter *painter);
    // @Override
    virtual void drawAssistLine(vsq::tick_t tick, QPainter *painter);
    // @Override
    virtual void sequenceChanged();
private:
    void _destroy();
    void _reset();
    QLabel *_labelFromEvent(const vsq::Event *e);

    int _noteHeight;
    PianoPainter high;
    PianoPainter middle;
    PianoPainter low;
    QList<QLabel *> _noteLabels;
};

#endif // NOTEVIEW_H
