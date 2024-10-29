# cub3D

<div align="center">
  <img src="assets/11_cub3d_review.jpg" alt="cub3D Review" width="800"/>
  
  [![42 Score](https://img.shields.io/badge/Score-100%2F100-success?style=for-the-badge&logo=42)](https://github.com/your-username/cub3d)
</div>

## Table of Contents
- [About](#about)
- [Requirements](#requirements)
- [Implementation](#implementation)
  - [Map Parsing](#map-parsing)
  - [Raycasting](#raycasting)
  - [Texture](#texture)
  - [Movement](#movement)
- [Optimization & Debug](#optimization--debug)
  - [Performance Tips](#performance-tips)
  - [Debug Tips](#debug-tips)
- [Usage](#usage)
- [Reference](#reference)

### 🗣️ About
Wolfenstein 3D 게임을 레이캐스팅(Raycasting) 기술을 사용해 구현하는 과제입니다.
2D 맵을 3D 시점으로 변환하고 텍스처를 입혀 실제 게임처럼 만듭니다.

### Requirements
• 필수 구현
  - 벽 충돌
  - 다른 색상의 벽면
  - 다른 텍스처의 벽면
  - 바닥/천장 색상

• 맵 요구사항
  - 맵은 6개 문자로 구성 (0, 1, N, S, E, W)
  - 맵은 벽으로 둘러싸여야 함
  - 맵 파일 확장자: .cub

### Implementation
#### Map Parsing
• 맵 파일 구조
```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

• 파싱 규칙
  - 텍스처 경로는 상대/절대 경로 모두 가능
  - RGB 값은 0-255 사이
  - 맵은 0(빈공간), 1(벽), NSEW(플레이어) 사용
  - 맵은 닫혀있어야 함 (flood fill로 검증)

• 맵 유효성 검사
```c
// 맵이 벽으로 둘러싸여 있는지 확인
static int	check_map_closed(char **map, t_point size, t_point curr)
{
    // 맵 범위를 벗어나면 실패
    if (curr.y < 0 || curr.y >= size.y || curr.x < 0 || curr.x >= size.x)
        return (0);
    // 벽이면 통과
    if (map[curr.y][curr.x] == '1')
        return (1);
    // 이미 방문했거나 맵 밖이면 실패
    if (map[curr.y][curr.x] == 'v' || map[curr.y][curr.x] == ' ')
        return (0);
    
    // 현재 위치 방문 표시
    map[curr.y][curr.x] = 'v';
    
    // 상하좌우 재귀적으로 확인
    if (!check_map_closed(map, size, (t_point){curr.x + 1, curr.y}) ||
        !check_map_closed(map, size, (t_point){curr.x - 1, curr.y}) ||
        !check_map_closed(map, size, (t_point){curr.x, curr.y + 1}) ||
        !check_map_closed(map, size, (t_point){curr.x, curr.y - 1}))
        return (0);
    return (1);
}
```

• 에러 처리
  - 파일 확장자 검사 (.cub)
  - 텍스처 파일 존재/형식 확인
  - RGB 값 범위 검사 (0-255)
  - 맵 요소 유효성 (0,1,N,S,E,W만 허용)
  - 플레이어 시작 위치 중복 검사
  - 빈 줄 처리

#### Raycasting
• 기본 원리
<div align="center">
  <img src="assets/raycasting_principle.png" alt="Raycasting Principle" width="600"/>
</div>
  - 시야각(FOV)만큼 광선 발사
  - 각 광선이 벽과 만나는 지점 계산
  - DDA 알고리즘으로 거리 계산
  - 거리에 따라 벽 높이 결정

• 구현 단계
  1. 플레이어 위치/방향 설정
    ```c
    // 플레이어 위치/방향 설정
    double posX, posY;
    double dirX, dirY;
    double planeX, planeY;
    ```
  2. 광선 방향 계산
    ```c
    // 화면의 x좌표마다 광선 계산
    for (int x = 0; x < screenWidth; x++) {
        // 카메라 평면상의 x좌표 (-1.0 ~ 1.0)
        double cameraX = 2 * x / (double)screenWidth - 1;
        
        // 광선의 방향 벡터 계산
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;
    }
    ```
  3. DDA 알고리즘으로 벽 찾기
    ```c
    // DDA 초기화
    double sideDistX, sideDistY;
    double deltaDistX = fabs(1 / rayDirX);
    double deltaDistY = fabs(1 / rayDirY);
    int stepX, stepY;

    // 광선이 왼쪽 또는 오른쪽으로 이동하는지
    if (rayDirX < 0) {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
    } else {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    }
    
    // 광선이 위쪽 또는 아래쪽으로 이동하는지
    if (rayDirY < 0) {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
    } else {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    }
    ```
  4. 어안 렌즈 효과 보정
  ```c
  // 어안 렌즈 효과 보정
  double perpWallDist;
  if (side == 0)
      perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
  else
      perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
  ```
  5. 벽 높이 계산
  ```c
  // 벽 높이 계산
  int lineHeight = (int)(screenHeight / perpWallDist);
  ```

• 수학적 요소
  - 삼각함수 (sin, cos)
  - 벡터 연산
  - DDA (Digital Differential Analysis)
  - 투영 변환

#### Texture
• 텍스처 처리
<div align="center">
  <img src="assets/texture_mapping.png" alt="Texture Mapping" width="600"/>
</div>
  - XPM 파일 로드
  - UV 좌표 계산
  - 벽면에 텍스처 매핑
  - 거리에 따른 음영 처리

• 구현 요소
  - 텍스처 로드
  - 텍스처 Y 좌표
  - 거리 기반 음영
  - 투명도 처리

1. 텍스처 로드
```c
typedef struct s_tex {
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
} t_tex;

// XPM 파일을 텍스처로 로드
int load_texture(t_tex *tex, char *path)
{
    tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
    if (!tex->img)
        return (ERROR);
    tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
                                 &tex->line_length, &tex->endian);
    return (SUCCESS);
}
```

2. UV 좌표 계산
```c
// 벽에 부딪힌 정확한 위치 계산
double wallX;
if (side == 0)
    wallX = posY + perpWallDist * rayDirY;
else
    wallX = posX + perpWallDist * rayDirX;
wallX -= floor(wallX);

// 텍스처 X 좌표
int texX = (int)(wallX * TEXWIDTH);
if (side == 0 && rayDirX > 0)
    texX = TEXWIDTH - texX - 1;
if (side == 1 && rayDirY < 0)
    texX = TEXWIDTH - texX - 1;

// Y 좌표 계산 (벽 높이에 따라)
for (int y = drawStart; y < drawEnd; y++)
{
    int texY = (int)((y * 2 - screenHeight + lineHeight) 
                     * (TEXHEIGHT / 2) / lineHeight);
    // 텍스처 색상 가져오기
    int color = tex->addr[texY * tex->line_length + texX 
                         * (tex->bits_per_pixel / 8)];
    // 거리에 따른 음영 처리
    if (side == 1)
        color = (color >> 1) & 8355711;
    buffer[y][x] = color;
}
```

3. 성능 최적화
```c
// 텍스처 버퍼링
typedef struct s_game {
    int buffer[screenHeight][screenWidth];
    int texture[4][texHeight * texWidth];
} t_game;

// 더블 버퍼링으로 깜빡임 방지
void render_frame(t_game *game)
{
    // 버퍼에 현재 프레임 그리기
    calculate_walls(game);
    draw_sprites(game);
    
    // 버퍼를 화면에 한 번에 출력
    for (int y = 0; y < screenHeight; y++)
        for (int x = 0; x < screenWidth; x++)
            game->img.data[y * screenWidth + x] = game->buffer[y][x];
    mlx_put_image_to_window(mlx, win, game->img.img, 0, 0);
}
```

• 최적화
  - 텍스처 미리 로드
  - 계산 결과 캐싱
  - 렌더링 순서 최적화

• 추가 기능
  - 다중 텍스처 관리
  - 투명도 처리
  - 텍스처 애니메이션
  - 밉맵 구현 (선택)

#### Movement
• 키보드 입력
  - W: 앞으로 이동
  - S: 뒤로 이동
  - A: 왼쪽으로 이동
  - D: 오른쪽으로 이동
  - ←: 왼쪽으로 회전
  - →: 오른쪽으로 회전
  - ESC: 종료

• 움직임 구현
  - 프레임 독립적인 이동
    ```c
    // 이동 속도 계산
    double moveSpeed = frameTime * 5.0;
    double rotSpeed = frameTime * 3.0;
    
    // 충돌 검사 후 이동
    if (keycode == W) {
        if (!worldMap[(int)(posX + dirX * moveSpeed)][(int)posY])
            posX += dirX * moveSpeed;
        if (!worldMap[(int)posX][(int)(posY + dirY * moveSpeed)])
            posY += dirY * moveSpeed;
    }
    ```
  - 벽 충돌 처리
  - 회전 처리
  - 부드러운 움직임

### Optimization & Debug
#### Performance Tips
• 연산 최적화
```c
// 1. 나눗셈 대신 곱셈 사용
double invDist = 1.0 / distance;  // 한 번만 계산
height = (int)(screenHeight * invDist);  // 나눗셈 대신 곱셈

// 2. 룩업 테이블 활용
static const float sin_table[360] = { ... };  // 미리 계산된 값
static const float cos_table[360] = { ... };

// 3. 비트 연산 활용
color = (color >> 1) & 0x7F7F7F;  // 50% 어둡게
```

• 메모리 최적화
```c
// 1. 더블 버퍼링
typedef struct s_img {
    void    *img;
    int     *data;
} t_img;

t_img    img[2];  // 두 개의 버퍼
int      current_buf;

// 버퍼 스왑
current_buf = !current_buf;
mlx_put_image_to_window(mlx, win, img[current_buf].img, 0, 0);

// 2. 텍스처 미리 로드
void    init_textures(t_game *game)
{
    static int loaded = 0;
    if (!loaded)
    {
        load_texture(&game->tex[0], "north.xpm");
        load_texture(&game->tex[1], "south.xpm");
        load_texture(&game->tex[2], "west.xpm");
        load_texture(&game->tex[3], "east.xpm");
        loaded = 1;
    }
}
```

#### Debug Tips
• 맵 디버깅
```c
// 2D 맵 시각화
void    debug_print_map(char **map, int height, int width)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
            printf("%c", map[y][x]);
        printf("\n");
    }
}

// 플레이어 정보 출력
void    debug_player_info(t_player *p)
{
    printf("Pos: (%f, %f)\n", p->x, p->y);
    printf("Dir: (%f, %f)\n", p->dir_x, p->dir_y);
    printf("Plane: (%f, %f)\n", p->plane_x, p->plane_y);
}
```

• 레이캐스팅 디버깅
```c
// 광선 정보 출력
void    debug_ray(t_ray *ray, int x)
{
    printf("Ray %d:\n", x);
    printf("Dir: (%f, %f)\n", ray->dir_x, ray->dir_y);
    printf("Distance: %f\n", ray->dist);
    printf("Wall height: %d\n", ray->line_height);
}

// FPS 표시
void    show_fps(t_game *game)
{
    char    fps[8];
    sprintf(fps, "FPS: %d", (int)(1.0 / game->frame_time));
    mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, fps);
}
```

### Usage
• 컴파일
```bash
make
```

• 실행
```bash
./cub3D maps/map.cub
```

• 맵 파일 형식
```
NO ./textures/wall_n.xpm    # 북쪽 벽 텍스처
SO ./textures/wall_s.xpm    # 남쪽 벽 텍스처
WE ./textures/wall_w.xpm    # 서쪽 벽 텍스처
EA ./textures/wall_e.xpm    # 동쪽 벽 텍스처

F 220,100,0                 # 바닥 색상 (RGB)
C 225,30,0                  # 천장 색상 (RGB)

# 맵 (1: 벽, 0: 빈공간, N/S/E/W: 플레이어 시작 위치/방향)
111111
100001
100N01
100001
111111
```

• 조작법
  - W, A, S, D: 이동
  - ←, →: 시점 회전
  - ESC: 종료

### Reference
• 레이캐스팅 학습
  - [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html)
  - [Ray-Casting Tutorial For Game Development](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
  - [Making a Basic 3D Engine in C](https://www.youtube.com/watch?v=gYRrGTC7GtA)

• 수학 개념
  - [DDA Algorithm](https://www.geeksforgeeks.org/dda-line-generation-algorithm-computer-graphics/)
  - [Vector Math](https://www.mathsisfun.com/algebra/vectors.html)
  - [Perspective Projection](https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/opengl-perspective-projection-matrix.html)

• MLX 라이브러리
  - [42 MLX Docs](https://harm-smits.github.io/42docs/libs/minilibx)
  - [MLX Tutorial](https://gontjarow.github.io/MiniLibX/)
  - [MLX Event Reference](https://github.com/42Paris/minilibx-linux/blob/master/README.md)

• 유용한 도구
  - [XPM Editor](https://www.online-image-editor.com/)
  - [Color Picker](https://colorpicker.me/)
  - [Map Editor](https://www.mapeditor.org/)