#!/usr/bin/python

from requests_html import HTMLSession
from bs4 import BeautifulSoup
import json
import time
import sys
import getopt
import os
import enum


def get_html(session, base_url, endpoint_url, id):
    try:
        response = session.get('{}{}{}'.format(base_url, endpoint_url, id))
        response.html.render()
    except:
        print("Error during GET nonograms/i/{}".format(id))
    else:
        if response.status_code == 200:
            return response.html.html
    return None


def parse_td(td):
    if td["class"][0] == "num_empty":
        return 0
    if td["class"][0] == "num":
        return int(td.find("div").text)


def get_nonogram_from_html(html, id):
    bs = BeautifulSoup(html, features="lxml")

    nonogram_table = bs.find("table", { "id": "nonogram_table", "class": "nonogram_table" })

    # Nonogram verticals block
    nmtt_body = nonogram_table.find("td", { "class": "nmtt" }).find("table").find("tbody")

    # Count of all `td` in any `tr` of nmtt_body is a count of verticals
    verticals_count = len(nmtt_body.find("tr").findAll("td"))
    verticals = [ [] for _ in range(verticals_count) ]

    nmtt_trs = nmtt_body.findAll("tr")
    for tr in nmtt_trs:
        nmtt_tds = tr.findAll("td")
        for i in range(len(nmtt_tds)):
            number = parse_td(nmtt_tds[i])
            if number != 0:
                verticals[i].append(number)

    # Nonogram horizontals block
    nmtl_body = nonogram_table.find("td", { "class": "nmtl" }).find("table").find("tbody")

    nmtl_trs = nmtl_body.findAll("tr")

    # Count of all `tr` of nmtl_body is a count of horizontals
    horizontals_count = len(nmtl_trs)
    horizontals = [ [] for _ in range(horizontals_count) ]

    for i in range(horizontals_count):
        tr = nmtl_trs[i]
        for td in tr:
            number = parse_td(td)
            if number != 0:
                horizontals[i].append(number)

    return { 'id': id, 'verticals': verticals, 'horizontals': horizontals }


def create_dir(dir):
    if not os.path.exists(dir):
        os.makedirs(dir)
        print("Created Directory : ", dir)
    else:
        print("Directory already existed : ", dir)
    return dir


def print_usage():
    print("usage: python3 crawler.py [-h] [--from] [--to]")


def save_nonogram(nonogram, id, output_dir):
    ID_PER_FOLDER = 1000

    folder_id = id // ID_PER_FOLDER
    path = '{}/{:02d}'.format(output_dir, folder_id)
    fullpath = '{}/{:05d}.json'.format(path, id)

    try:
        with open(fullpath, 'w') as json_file:
            json.dump(nonogram, json_file)
    except:
        create_dir(path)
        try:
            with open(fullpath, 'w') as json_file:
                json.dump(nonogram, json_file)
        except:
            return False
    return True


class NonogramType(enum.Enum):
    black_and_white = 1
    colour = 2

class NonogramCrawler:
    NONOGRAM_MIN_INDEX = 1
    NONOGRAM_MAX_INDEX = 54216
    DEFAULT_OUTPUT_DIR = "nonograms"
    DEFAULT_SLEEP_AFTER_ERROR = 0.25

    def __init__(self):
        self.nonogram_type = NonogramType.black_and_white
        self.base_url = 'https://www.nonograms.ru/'
        self.endpoint_url = 'nonograms/i/'
        self.id_from = NonogramCrawler.NONOGRAM_MIN_INDEX
        self.id_to = NonogramCrawler.NONOGRAM_MAX_INDEX
        self.output_dir = NonogramCrawler.DEFAULT_OUTPUT_DIR
        self.sleep_after_error = NonogramCrawler.DEFAULT_SLEEP_AFTER_ERROR


    def set_type(self, nonogram_type: NonogramType):
        self.nonogram_type = nonogram_type
        if nonogram_type == NonogramType.black_and_white:
            self.endpoint_url = 'nonograms/i/'
        elif nonogram_type == NonogramType.colour:
            self.endpoint_url = 'nonograms2/i/'


    def set_id_from(self, id):
        self.id_from = id


    def set_id_to(self, id):
        self.id_to = id
    

    def run(self):
        session = HTMLSession()

        for id in range(self.id_from, self.id_to + 1):
            html = get_html(session, self.base_url, self.endpoint_url, id)

            if html is None:
                time.sleep(self.sleep_after_error)
                continue

            nonogram = get_nonogram_from_html(html, id)
            
            if save_nonogram(nonogram, id, self.output_dir):
                print("nonograms/i/{} crawled successfully".format(id))
            else:
                print("failed to save nonograms/i/{}".format(id))


def main(argv):
    crawler = NonogramCrawler()

    try:
        opts, args = getopt.getopt(argv, "h", [ "from=", "to=", "type=", "output_dir=" ])
    except getopt.GetoptError:
        print_usage()
        sys.exit(2)

    for opt, arg in opts:
        if opt == "-h":
            print_usage()
        elif opt == "--from":
            crawler.set_id_from(int(arg))
        elif opt == "--to":
            crawler.set_id_to(int(arg))
        elif opt == "--type":
            crawler.set_type(NonogramType[arg])
        elif opt == "--output_dir":
            crawler.set_output_dir = arg
    
    crawler.run()

    print("Crawler work ended")


if __name__ == "__main__":
    main(sys.argv[1:])
