/*
 *
 *    AbstractSequenceView.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/16
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef ABSTRACTSEQUENCEVIEW_H
#define ABSTRACTSEQUENCEVIEW_H

#include <QWidget>
#include <Sequence.hpp>

namespace vsq
{
class Sequence;
}
class Selection;
class SequenceModel;

/**
 *  @brief シーケンスを表示する基底クラス．
 */
class AbstractSequenceView : public QWidget
{
    Q_OBJECT
public:
    /**
     *  @brief 与えられた値で初期化します．
     *  @param [in] model 表示すべきシーケンスモデル．
     *  @param [in] parent 親 Widget ．
     */
    explicit AbstractSequenceView(SequenceModel *model, QWidget *parent);

    /**
     *  @brief  表示すべきシーケンスを変更します．
     *          与えられたシーケンスは view クラス内では変更できません．
     *  @param [in] sequence 変更後のシーケンス．
     */
    void setModel(SequenceModel *model);

    /**
     *  @brief  ビューが保持しているモデルを返します．
     */
    SequenceModel *model();
    const SequenceModel *model() const;

protected:
    // @Override
    virtual void paintEvent(QPaintEvent *e);

    /**
     *  @brief  モデルが変更された時に呼び出されます．
     *          このメソッドをオーバーライドすることでシーケンス変更時の処理が記述できます．
     */
    virtual void modelChanged(){ }

signals:
    
public slots:
    /**
     *  @brief 該当する領域を描画します．
     *  @param [in] region 描画すべき領域．
     *  @param [in/out] painter 描画対象から得た QPainter クラスへのポインタ．
     */
    void paint(const QRegion &region, QPainter *painter);

    /**
     *  @brief 該当する矩形を描画します．
     *  @param [in] rect 描画すべき矩形．
     *  @param [in/out] painter 描画対象から得た QPainter クラスへのポインタ．
     */
    virtual void paint(const QRect &rect, QPainter *painter) = 0;

    /**
     *  @brief 表示すべきトラックが変更された際に通知を受け取るスロットです．
     */
    virtual void trackChanged(int id);

    /**
     *  @brief 四分音符の幅が変更された際に通知を受け取るスロットです．
     */
    virtual void beatWidthChanged(int w) = 0;

    /**
     *  @brief 音符の高さが変更された際に通知を受け取るスロットです．
     */
    virtual void noteHeightChanged(int h) = 0;
private:
    SequenceModel *_model;          //! @brief 現在保持しているモデル

    QWidget *_parent;               //! @brief 親Widget
};

#endif // ABSTRACTSEQUENCEVIEW_H
