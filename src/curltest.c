#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct memory {
  char *response;
  size_t size;
};

size_t write_callback(char *data, size_t size, size_t nmemb, void *userp) {
  size_t realsize = size * nmemb;
  struct memory *mem = (struct memory *)userp;

  char *ptr = realloc(mem->response, mem->size + realsize + 1);
  if (ptr == NULL)
    return 0; /* out of memory! */

  mem->response = ptr;
  memcpy(&(mem->response[mem->size]), data, realsize);
  mem->size += realsize;
  mem->response[mem->size] = 0; // why?

  return realsize;
}

int main(void) {
  CURL *curl;
  CURLcode res;

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();

  if (curl) {
    struct memory *mem = malloc(sizeof(struct memory));
    mem->response = malloc(1);

    curl_easy_setopt(curl, CURLOPT_URL, "https://zdf-hls-17.akamaized.net/hls/live/2016500/de/high/master.m3u8");
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, mem);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    curl_easy_cleanup(curl);

    printf("%s\n", mem->response);
    free(mem->response);
    free(mem);
  }

  curl_global_cleanup();

  return 0;
}
