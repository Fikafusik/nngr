#!/usr/bin/python

from requests_html import HTMLSession
from bs4 import BeautifulSoup
import json
import time
import sys
import getopt
import os

def get_html(id, session):
    try:
        response = session.get('https://www.nonograms.ru/nonograms/i/{}'.format(id))
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


def get_nonogram_from_html(html):
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

    return { 'verticals': verticals, 'horizontals': horizontals }


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


def main(argv):
    NONOGRAM_MIN_INDEX = 1
    NONOGRAM_MAX_INDEX = 54216
    DEFAULT_OUTPUT_DIR = "nonograms"

    id_from = NONOGRAM_MIN_INDEX
    id_to = NONOGRAM_MAX_INDEX
    output_dir = DEFAULT_OUTPUT_DIR

    try:
        opts, args = getopt.getopt(argv,"h", ["from=", "to=", "output_dir="])
    except getopt.GetoptError:
        print_usage()
        sys.exit(2)

    for opt, arg in opts:
        if opt == "-h":
            print_usage()
        elif opt == "--from":
            id_from = int(arg)
        elif opt == "--to":
            id_to = int(arg)
        elif opt == "--output_dir":
            output_dir = arg
    
    print("id range: ({}, ..., {})".format(id_from, id_to))

    session = HTMLSession()

    for id in range(id_from, id_to + 1):
        html = get_html(id, session)

        if html is None:
            time.sleep(0.25)
            continue

        nonogram = get_nonogram_from_html(html)
        
        if save_nonogram(nonogram, id, output_dir):
            print("nonograms/i/{} crawled successfully".format(id))
        else:
            print("failed to save nonograms/i/{}".format(id))


if __name__ == "__main__":
    main(sys.argv[1:])
