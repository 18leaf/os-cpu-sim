import pandas as pd
import plotly.express as px

def main():
    # load data
    df = pd.read_csv('../results_detailed.csv')

    # make sure numeric
    num_cols = ['arrival','burst','start','exit','waiting','turnaround','response']
    for col in num_cols:
        df[col] = pd.to_numeric(df[col], errors='coerce')
    # drop invalid comlumns
    df = df.dropna(subset=num_cols)


    # histogram of waiting time
    fig1 = px.histogram(
        df,
        x='waiting',
        color='scheduler',
        barmode='overlay',
        nbins=50,
        title='Waiting Time Distribution by Scheduler',
        labels={'waiting': 'Waiting Time (ticks)'},
        template='plotly_dark'
    )
    fig1.show()

    # box plot - turnaround time
    fig2 = px.box(
        df,
        x='scheduler',
        y='turnaround',
        title='Turnaround Time by Scheduler',
        labels={'scheduler': 'Algorithm', 'turnaround': 'Turnaround Time (ticks)'},
        template='plotly_dark'

    )
    fig2.show()

    # scatter plot arrival vs exit
    fig3 = px.scatter(
        df,
        x='arrival',
        y='exit',
        color='scheduler',
        title='Arrival vs. Exit Time by Algorithm',
        labels={'arrival': 'Arrival (ticks)', 'exit': 'Exit (ticks)'},
        template='plotly_dark'
    )
    fig3.show()

    # box chart of avg waiting turnaround and response times
    metrics = (
        df
        .groupby('scheduler')[['waiting','turnaround','response']]
        .mean()
        .reset_index()
    )
    fig4 = px.bar(
        metrics,
        x='scheduler',
        y=['waiting','turnaround','response'],
        barmode='group',
        title='Average Waiting, Turnaround & Response Times',
        labels={'value':'Time (ticks)','scheduler':'Algorithm'},
        template='plotly_dark'
    )
    fig4.show()

if __name__ == '__main__':
    main()

