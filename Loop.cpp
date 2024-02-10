#include <chrono>
#include <cstdlib>
#include <gtk/gtk.h>
#include <iostream>
#include <iterator>
#include <string>
#include <unistd.h>

#include "Controls.h"
#include "Direction.h"
#include "Entity.h"
#include "GravitySimulation.h"
#include "LegalDistances.h"
#include "MapCollisionHandling.h"

using namespace std;
using namespace chrono;
using std::begin;
using std::end;

static uint64_t oldTime = 0;
static uint64_t newTime = 0;

struct mapDimensions {
  float dimX = 800;
  float dimY = 800;
  float dimZ = 800;
};

static GravitySimulation gSim(9.1, 0.1);
static Controls controls;
static Entity myPlayer(100, 50, 500, 75, 10, 10, 10);
static Entity myBox(400, 80, 500, 10, 30, 30, 30);
static Entity myBox2(650, 200, 500, 10, 30, 30, 30);
static Entity *myMapEntities[10];
static mapDimensions gameMap;
static MapCollisionHandling mapCollisionHandling(gameMap.dimX, gameMap.dimY,
                                                 gameMap.dimZ);

static GtkWidget *area;

/* static void print_hello (GtkWidget *widget, gpointer data)
{
        g_print ("Hello World\n");
} */

static void handle_key_pressed(GtkEventControllerKey *self, guint keyval,
                               guint keycode, GdkModifierType state,
                               gpointer user_data) {
  g_print("Press from key %d\n", keycode);

  controls.press(keycode);
}

static void handle_key_released(GtkEventControllerKey *self, guint keyval,
                                guint keycode, GdkModifierType state,
                                gpointer user_data) {
  // g_print ("Release from key %d\n", keycode);

  controls.release(keycode);
}

static void draw_function(GtkDrawingArea *area, cairo_t *cr, int width,
                          int height, gpointer data) {
  cairo_rectangle(cr, myPlayer.getX() - myPlayer.getDimX(),
                  height - myPlayer.getY() - myPlayer.getDimY(),
                  myPlayer.getDimX() * 2, myPlayer.getDimY() * 2);
  for (int i = 0; i < 2; i++) {
    Entity *e = myMapEntities[i];
    cairo_rectangle(cr, e->getX() - e->getDimX(),
                    height - e->getY() - e->getDimY(), e->getDimX() * 2,
                    e->getDimY() * 2);
  }
  cairo_set_source_rgb(cr, 0.7, 0.4, 0.6);

  cairo_fill(cr);
}

static gboolean handle_tick(GtkWidget *widget, GdkFrameClock *frame_clock,
                            gpointer user_data) {
  newTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch())
                .count();

  if (newTime - oldTime > 10) {
    LegalDistances legalDistances =
        mapCollisionHandling.getLegalMovement(&myPlayer, myMapEntities, 2);

    if (controls.isPressed(65)) {
      float maxFlyDistance =
          mapCollisionHandling.getMaxFlyDistance(&myPlayer, myMapEntities, 2);
      // cout << "MAX FLY" << maxFlyDistance << endl;
      myPlayer.fly(10 < maxFlyDistance ? 10 : maxFlyDistance);
    }
    if (controls.isPressed(113)) {
      float oldX = myPlayer.getX();
      myPlayer.move(Direction::XBACKW, 2);
      if (mapCollisionHandling.colliding(&myPlayer, myMapEntities, 2)) {
        myPlayer.setX(oldX);
      }
    }
    if (controls.isPressed(114)) {
      float oldX = myPlayer.getX();
      myPlayer.move(Direction::XFORW, 2);
      if (mapCollisionHandling.colliding(&myPlayer, myMapEntities, 2)) {
        myPlayer.setX(oldX);
      }
    }
    if (controls.isPressed(116)) {
      float oldZ = myPlayer.getZ();
      myPlayer.move(Direction::ZBACKW, 2);
      if (mapCollisionHandling.colliding(&myPlayer, myMapEntities, 2)) {
        myPlayer.setZ(oldZ);
      }
    }
    if (controls.isPressed(111)) {
      float oldZ = myPlayer.getZ();
      myPlayer.move(Direction::ZFORW, 2);
      if (mapCollisionHandling.colliding(&myPlayer, myMapEntities, 2)) {
        myPlayer.setZ(oldZ);
      }
    }

    float maxFallDistance =
        mapCollisionHandling.getMaxFallDistance(&myPlayer, myMapEntities, 2);
    if (maxFallDistance > 0) {
      myPlayer.setFalling(true);
    }

    float fallDistance = 0;
    if (myPlayer.isFalling()) {
      float seconds = (myPlayer.getFallTime() + 10) / 1000.0;
      float simFallDistance = gSim.getDistance(seconds, myPlayer.getMass());
      simFallDistance = simFallDistance < 0 ? 0 : simFallDistance;
      fallDistance =
          simFallDistance < maxFallDistance ? simFallDistance : maxFallDistance;
      if (fallDistance <= 0) {
        myPlayer.stopFalling();
      } else {
        myPlayer.fall(myPlayer.getFallTime() + 10, fallDistance);
      }
    }

    /* g_print("Player posX: %f\n", myPlayer.getX());
    g_print("Player posY: %f\n", myPlayer.getY());
    g_print("Player posZ: %f\n", myPlayer.getZ()); */
    gtk_widget_queue_draw(area);
    oldTime = newTime;
  }

  return G_SOURCE_CONTINUE;
}

static void activate(GtkApplication *app, gpointer user_data) {
  myMapEntities[0] = &myBox;
  myMapEntities[1] = &myBox2;
  // myPlayer.fall(10, 10);

  GtkWidget *window;
  // GtkWidget *button;

  GtkEventController *keyCtrl;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Simple Arena");
  gtk_window_set_default_size(GTK_WINDOW(window), 1000, 1000);

  area = gtk_drawing_area_new();
  gtk_drawing_area_set_content_width(GTK_DRAWING_AREA(area), 800);
  gtk_drawing_area_set_content_height(GTK_DRAWING_AREA(area), 800);
  gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(area), draw_function, NULL,
                                 NULL);
  gtk_widget_set_valign(area, GtkAlign::GTK_ALIGN_CENTER);
  gtk_window_set_child(GTK_WINDOW(window), area);

  /* button = gtk_button_new_with_label ("Hello World");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  gtk_window_set_child (GTK_WINDOW (window), button); */

  keyCtrl = gtk_event_controller_key_new();
  g_signal_connect(keyCtrl, "key-pressed", G_CALLBACK(handle_key_pressed),
                   NULL);
  g_signal_connect(keyCtrl, "key-released", G_CALLBACK(handle_key_released),
                   NULL);
  gtk_widget_add_controller(window, keyCtrl);

  gtk_widget_add_tick_callback(window, handle_tick, NULL, NULL);

  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
  GtkApplication *app;
  int status;

  app = gtk_application_new("com.flikkes.simplearena",
                            G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
