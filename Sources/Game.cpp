#include "Game.hpp"


// TODO: 砲台の位置を画面左に、ターゲットの位置を画面右に移動させる。(A)
// TODO: 雲の位置を左から右に動かす。見えなくなったら左端に戻す。(B)
// TODO: 砲台を青い壁に沿って上下に動かす。(C)
// TODO: 弾のスピードを速くし、弾が画面右端を通り越したら再度発射可能にする。(D)
// TODO: スコアのサイズを大きくする。(E)
// TODO: スコアを100点ずつ加算するようにし、5桁の表示に変える。(F)
// TODO: PlayBGM()関数を使って、BGMを再生する。(G)
// TODO: PlaySE()関数を使って、弾の発射時とターゲットに当たった時にSEを再生する。(H)


Vector2 cloudPos;       //!< 雲の位置
Vector2 cannonPos;      //!< 砲台の位置
Vector2 bulletPos;      //!< 弾の位置
Rect    targetRect;     //!< ターゲットの矩形
int     score;          //!< スコア
bool    flag = true;    //!< 砲台の位置判定

// ゲーム開始時に呼ばれる関数です。
void Start()
{
    cloudPos = Vector2(-320, 100);
    cannonPos = Vector2(-300, -150);            // 砲台の位置変更(HW16A115 田中雄登)
    targetRect = Rect(275, -140, 40, 40);       // ターゲットの位置変更(HW16A115 田中雄登)
    bulletPos.x = -999;
    score = 0;
    
    PlayBGM("bgm_maoudamashii_8bit07.mp3"); //BGMを追加（HW16A114 田中陽大）

}

// 1/60秒ごとに呼ばれる関数です。モデルの更新と画面の描画を行います。
void Update()
{
    // 弾の発射
    if (bulletPos.x <= -999 && Input::GetKeyDown(KeyMask::Space)) {
        bulletPos = cannonPos + Vector2(50, 10);
        PlaySound("se_maoudamashii_system20.mp3"); //発射時のSEを追加（HW16A114 田中陽大）
    }

    // 弾の移動
    if (bulletPos.x > -999) {       // 弾の速度とリロードの変更(HW16A115 田中雄登)
        bulletPos.x += 70 * Time::deltaTime;
        if (bulletPos.x > 320) {
            bulletPos.x = -999;
        }

        // ターゲットと弾の当たり判定
        Rect bulletRect(bulletPos, Vector2(32, 20));
        if (targetRect.Overlaps(bulletRect)) {
            score += 100;         // スコアの加算、スコアを+100Pに変更 （HW16A114 田中陽大）
            bulletPos.x = -999; // 弾を発射可能な状態に戻す
            PlaySound("se_maoudamashii_explosion06.mp3"); //ターゲットに被弾時のSEを追加（HW16A114 田中陽大）
        }
    }

    // 背景の描画
    Clear(Color::cyan);
    FillRect(Rect(-320, -240, 640, 100), Color::green);

    // 雲の描画
    if (cloudPos.x < 320) {     // 雲が移動するように変更し、折り返すように変更(HW16A115 田中雄登)
        cloudPos.x += 100 * Time::deltaTime;
        DrawImage("cloud1.png", cloudPos);
    }
    if (cloudPos.x > 320) {
        cloudPos.x = -320;
        DrawImage("cloud1.png", cloudPos);
    }

    // 弾の描画
    if (bulletPos.x > -999) {
        DrawImage("bullet.png", bulletPos);
    }

    // 砲台の描画
    FillRect(Rect(cannonPos.x-10, -140, 20, 100), Color::blue);
    if (cannonPos.y <= -140){       // 砲台の位置が壁に沿って移動するように変更(HW16A115 田中雄登)
        flag = true;
    }
    if (cannonPos.y >= -70) {
        flag = false;
    }
    if (flag == true) {
        cannonPos.y += 3;
    }else{
        cannonPos.y -= 3;
    }

    DrawImage("cannon.png", cannonPos);

    // ターゲットの描画
    FillRect(targetRect, Color::red);

    // スコアの描画
    SetFont("nicoca_v1.ttf", 20.0f);
    DrawText(FormatString("%05d", score), Vector2(-319, 199), Color::black);
    DrawText(FormatString("%05d", score), Vector2(-320, 200), Color::white);
    //スコアを5桁に変更 （HW16A114 田中陽大）

}

